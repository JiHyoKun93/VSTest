#include "stdafx.h"
#include "GameSystem.h"
#include "ItemWhipComponent.h"
#include "ItemMagicWandComponent.h"
#include "ItemGarlicComponent.h"
#include "ItemBookComponent.h"
#include "Bullet.h"
#include "DropItemNode.h"
#include "SceneIngame.h"
#include "CameraFollowing.h"
#include "GameData.h"
#include "GameEventHandling.h"
#include "GameSound.h"
#include "SceneResult.h"
#include "ItemManagementSystem.h"

static GameSystem* instance = nullptr;

GameSystem* GameSystem::getInstance() {
	//if (instance == nullptr) instance = new GameSystem();
	//return instance;
	return instance == nullptr ? instance = new GameSystem() : instance;
}

static double expRequires[] = {
	0, 100, 300, 800
};

GameSystem::GameSystem() {
	data = GameData::getInstance();
	evt = GameEventHandling::getInstance();
	sound = SoundSystem::getInstance();

	evt->setGameSystem(this);
	PositionComponent::loadDocument();
}

double GameSystem::calcExpFomular(int level){
	// 경험치통 레벨에 따라 점점 늘어가는 방식 
	// 최대 레벨이 존재하지 않음
	auto ret = (level - 1) * 120 * pow(2, level - 2);
	return ret;
}

double GameSystem::calcExpSheet(int level){
	// 경험치통을 정해두는 방식
	// 단점? = 최대 레벨이 존재(만렙)
	return expRequires[level];
}

void GameSystem::setHero(Hero* value){
	this->hero = value;
}

void GameSystem::setHeroIndex(int index){
	this->heroIndex = index;
}

Hero* GameSystem::getHero(){
	return this->hero;
}

int GameSystem::getHeroIndex(){
	return this->heroIndex;
}

void GameSystem::stageStart(int stageNumber, float timeLimitsec){
	state = GameState::PLAYING;
	this->stageNumber = stageNumber;
	this->timeLimit = timeLimitsec;
	currentScene->setMap(createMap(stageNumber));
}

void GameSystem::stageFailed(){
	state = GameState::FAILED;
}

void GameSystem::stageVictory(){
	state = GameState::VICTORY;
}

void GameSystem::stagePause(){
	state = GameState::PAUSED;
}

void GameSystem::stageResume(){
	state = GameState::PLAYING;
}

GameState GameSystem::getGameState() {
	return state;
}

Monster* GameSystem::getNearestMonster(){
	if (!isStatePlaying()) return nullptr;

	Node* nearest = nullptr;
	float nearestDistance = 9999999999999.0f;
	auto children = ingameMonsterNode->getChildren();
	for (auto it = children.begin(); it != children.end(); it++) {
		Node* child = *it;
		float distance = child->getPosition().distance(heroNode->getPosition());
		if (distance < nearestDistance) {
			nearest = child;
			nearestDistance = distance;
		}
	}
	return (Monster*)nearest;
}

ExScene* GameSystem::getCurrentScene() {
	return currentScene;
}

void GameSystem::setCurrentScene(ExScene* scene){
	this->currentScene = scene;

	moveVector = Vec2::ZERO;

	auto keybd = EventListenerKeyboard::create();
	keybd->onKeyPressed = std::bind(&GameEventHandling::onKeyPressed, evt, std::placeholders::_1, std::placeholders::_2);
	keybd->onKeyReleased = std::bind(&GameEventHandling::onKeyReleased, evt, std::placeholders::_1, std::placeholders::_2);
	
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keybd, currentScene);

	if (currentScene->getName().compare("SceneIngame") == 0) {
		currentScene->schedule(std::bind(&GameSystem::logicIngame, this, std::placeholders::_1), "logicIngame");
		state = GameState::PLAYING;
		data->setStageKills(0);
		data->setStageTime(0);

		stageStart(1, 60 * 30);

		ingameMonsterNode = currentScene->getOrCreateNodeInMap("ingameMonsterNode");
		ingameExpNode = currentScene->getOrCreateNodeInMap("ingameExpNode");
		ingameItemNode = currentScene->getOrCreateNodeInMap("ingameItemNode");

		
		currentScene->schedule(std::bind(&GameSystem::logicTimer, this, std::placeholders::_1), "logicTimer");
	}

	auto contact = EventListenerPhysicsContact::create();

	contact->onContactBegin = std::bind(&GameSystem::onContactBegin, this, std::placeholders::_1);
	contact->onContactSeparate = std::bind(&GameSystem::onContactSeparate, this, std::placeholders::_1);
	currentScene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contact, currentScene);
	//auto pad = EventListenerController::create();
	//pad->onAxisEvent();//콘솔 엄지로 돌리는거
	//scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(pad, currentScene);

}

void GameSystem::logicIngame(float dt) {
	if (monsterSize < 20) {
		spawnMonster();
	}
	/*
	TMXTiledMap* map;
	Vec2 pos;

	if (playerTilePos != pos) {
		for (int i = pos.x - 20; i < pos.x + 20; i++) {
			for (int k = pos.y - 20; k < pos.y + 20; k++) {
				auto body = PhysicsBody::createBox();
				map->getLayer("")->getTileAt(Vec2(i, k))->addComponent(body);
			}
		}
	}
	*/
}

void GameSystem::logicTimer(float dt){
	if (!isStatePlaying()) return;

	data->addStageTime(dt);
	float totalSec = data->getStageTime();

	int sec = (int)totalSec % 60;
	int min = (int)totalSec / 60;
	int hour = min / 60;

	char line[20];
	sprintf(line, "%02d:%02d", min, sec);
	((SceneIngame*)currentScene)->setTimerString(line);
}

void GameSystem::spawnMonster() {
	if (!isStatePlaying()) return;

	Monster* monster = Monster::create();
	ingameMonsterNode->addChild(monster);
	auto body = PhysicsBody::createBox(Size(20, 20));
	body->setCategoryBitmask(BITMASK_COLLISION_MONSTER);
	body->setContactTestBitmask(BITMASK_COLLISION_MONSTER);
	body->setCollisionBitmask(BITMASK_COLLISION_MONSTER);
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	monster->addComponent(body);

	Vec2 heroPos = heroNode->getPosition();
	float angle = RandomHelper::random_real<float>(0, 2 * 3.141592);
	float r = 800;
	Vec2 spawnPos = heroPos + Vec2(r * cosf(angle), r * sinf(angle));
	monster->setPosition(spawnPos);

	monster->schedule([=](float dt)->void {
		Vec2 delta = heroNode->getPosition() - monster->getPosition();
		body->setVelocity(delta.getNormalized() * BASIC_MOVEMENT_SPEED_MONSTER);
	}, "logic");
	monsterSize++;

	monster->setOnExitCallback([=]() { monsterSize--; });
}

void GameSystem::dropExpItemAtPosition(const Vec2& position, float expValue){
	if (!isStatePlaying()) return;

	DropItemNode* n = DropItemNode::create(ItemType::EXP);
	n->setValue(expValue);
	// 판정 방법 2가지 
	// 1 <-- Magnet
	// 2 <-- 획득

	// 현재 오류 있음, position이 이상함?
	n->scheduleOnce([=](float dt)->void {
		n->setPosition(position);
		PhysicsBody* body = PhysicsBody::createCircle(20);
		body->setCategoryBitmask(BITMASK_COLLISION_ITEM);
		body->setContactTestBitmask(BITMASK_CONTACT_ITEM);
		body->setCollisionBitmask(BITMASK_COLLISION_ITEM);
		body->setGravityEnable(false);
		body->setRotationEnable(false);
		body->setDynamic(false);
		n->addComponent(body);
	}, 0.00000001f, "logic");

	currentScene->addChild(n);
}

void GameSystem::dropGoldItemAtPosition(const Vec2& position, float expValue){
	if (!isStatePlaying()) return;

	DropItemNode* n = DropItemNode::create(ItemType::GOLD);
	n->setValue(expValue);
	// 판정 방법 2가지 
	// 1 <-- Magnet
	// 2 <-- 획득

	PhysicsBody* body = PhysicsBody::createCircle(20);
	body->setCategoryBitmask(BITMASK_COLLISION_ITEM);
	body->setContactTestBitmask(BITMASK_CONTACT_ITEM);
	body->setCollisionBitmask(BITMASK_COLLISION_ITEM);
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	body->setDynamic(false);
	n->setPosition(position);

	n->addComponent(body);

	ingameItemNode->addChild(n);
}

void GameSystem::dropChickenItemAtPosition(const Vec2& position, float expValue){
	if (!isStatePlaying()) return;

	DropItemNode* n = DropItemNode::create(ItemType::CHICKEN);
	n->setValue(expValue);
	// 판정 방법 2가지 
	// 1 <-- Magnet
	// 2 <-- 획득

	PhysicsBody* body = PhysicsBody::createCircle(50);
	body->setCategoryBitmask(BITMASK_COLLISION_ITEM);
	body->setContactTestBitmask(BITMASK_CONTACT_ITEM);
	body->setCollisionBitmask(BITMASK_COLLISION_ITEM);
	body->setGravityEnable(false);
	body->setRotationEnable(false);
	body->setDynamic(false);
	n->setPosition(position);
	n->addComponent(body);

	ingameItemNode->addChild(n);
}

bool GameSystem::onContactBegin(PhysicsContact& contact){
	if (!isStatePlaying()) return true;

	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	PhysicsBody* player = checkBitmask(a, b, BITMASK_COLLISION_PLAYER);
	PhysicsBody* bullet = checkBitmask(a, b, BITMASK_COLLISION_BULLET);
	PhysicsBody* monster = checkBitmask(a, b, BITMASK_COLLISION_MONSTER);
	PhysicsBody* item = checkBitmask(a, b, BITMASK_COLLISION_ITEM);

	if (bullet && monster) onContactBulletAndMonster(bullet, monster);
	if (monster && player) onContactMosterAndPlayer(monster, player);
	if (item && player) {
		onContactItemAndPlayer(item, player);
		return false;
	}
	if (item && monster) return false;

	return true;
}

bool GameSystem::onContactSeparate(PhysicsContact& contact){
	if (!isStatePlaying()) return true;

	auto a = contact.getShapeA()->getBody();
	auto b = contact.getShapeB()->getBody();

	PhysicsBody* player = checkBitmask(a, b, BITMASK_COLLISION_PLAYER);
	PhysicsBody* monster = checkBitmask(a, b, BITMASK_COLLISION_MONSTER);

	if (monster && player) {
		PlayerNode* playerNode = (PlayerNode*)player->getOwner();
		if (playerNode->getHp() <= 0) CCLOG("GAME OVER");

		playerNode->nearMonsterCounter -= 1;
	}
	return true;
}

void GameSystem::onContactBulletAndMonster(PhysicsBody* bullet, PhysicsBody* monster){
	if (!isStatePlaying()) return;

	BulletNode* bulletNode = (BulletNode*)bullet->getOwner();
	float damage = bulletNode->damage;

	if (bulletNode == nullptr) return;

	Monster* monsterNode = (Monster*)monster->getOwner();
	if (monsterNode == nullptr) return;

	monsterNode->addHp(-damage);

	char line[24];
	sprintf(line, "%.0f", damage);
	Label* label = Label::createWithTTF(line, FONT_DEFUALT, 24.0f);
	label->setPosition(monsterNode->getPosition() + Vec2(0, 20));
	currentScene->addChild(label);
	label->runAction(Sequence::create(
		JumpBy::create(0.2, Vec2(50, 0), 30, 1), JumpBy::create(0.2, Vec2(25, 0), 10, 1), RemoveSelf::create(), nullptr
	));

	if (monsterNode->getHp() <= 0.0f) {
		dropExpItemAtPosition(monsterNode->getPosition(), 100);

		monsterNode->removeFromParent();
		//TODO : kill score++;
		data->addStageKills(1);
		char line[24];
		sprintf(line, "Kills : %d", data->getStagetKills());
		((SceneIngame*)currentScene)->tKills->setString(line);
	}

	if (!bulletNode->isPiercing) bulletNode->removeFromParent();
}

void GameSystem::onContactMosterAndPlayer(PhysicsBody* monster, PhysicsBody* player){
	if (!isStatePlaying()) return;

	PlayerNode* playerNode = (PlayerNode*)player->getOwner();
	if (playerNode->getHp() <= 0) CCLOG("GAME OVER");

	playerNode->nearMonsterCounter += 1;
}

void GameSystem::onContactItemAndPlayer(PhysicsBody* item, PhysicsBody* player){
	// 플레이 또는 시간정지 상태가 아니라면
	// 즉 일시정지, 레디, 빅토리, 패배 상태일경우 동작하지 않는 if 구문
	if (!(isStatePlaying() || isStateTimeStop())) return;

	float value = ((DropItemNode*)item->getOwner())->getValue();
	ItemType type = ((DropItemNode*)item->getOwner())->getType();
	if (type == ItemType::EXP) {
		// 플레이어에게 경험치를
		addPlayerExp(value);
	}
	if (type == ItemType::CHICKEN) {
		// 플레이어에게 체력을 

	}
	if (type == ItemType::GOLD) {
		// 플레이어에게 골드를

	}

	item->getOwner()->removeFromParent();
}



void GameSystem::addPlayerExp(double exp){
	if (!isStatePlaying()) return;

	data->addStageExp(exp);

	double minExp = calcExpFomular(data->getStagePlayerLevel());
	double maxExp = calcExpFomular(data->getStagePlayerLevel() + 1);

	// 경험치 % 구하는 공식
	double ratio = (data->getStageExp() - minExp) / (maxExp - minExp);
	double percent = ratio * 100.0;

	bool lvUp = maxExp <= data->getStageExp();
	if (lvUp) {
		data->setStagePlayerLevel(data->getStagePlayerLevel() + 1);
		// TODO : 렙업시 특별한 동작을 하게 만듬
		//CCLOG("Level Up! %d", data->getStagePlayerLevel());
		setState(GameState::PAUSED);
		((SceneIngame*)currentScene)->showLevelUpDialog();
	}
	
	if (state == GameState::PLAYING) {
		SceneIngame* ingame = (SceneIngame*)currentScene;
		ingame->pbExp->setPercent((float)percent);
	}

}

void GameSystem::setPlayerSpawnPoint(const Vec2& pos){
	this->playerSpawnPoint = pos;
}

void GameSystem::createHeroInCurrentScene(){
	if (currentScene == nullptr) return;
	if (currentScene->getName().compare("SceneIngame") != 0) return;

	ItemManageMentSystem::getInstance()->initInfo();

	heroNode = PlayerNode::create();
	currentScene->getMap()->addChild(heroNode);
	auto body = PhysicsBody::createBox(Size(20, 20));
	body->setGravityEnable(false);
	body->setRotationEnable(false); // 다른 객체와 겹쳐도 돌지 않음(회전x)
	body->setCategoryBitmask(BITMASK_COLLISION_PLAYER);
	body->setContactTestBitmask(BITMASK_CONTACT_PLAYER);
	body->setCollisionBitmask(BITMASK_COLLISION_PLAYER);
	heroNode->addComponent(body);

	auto camera = currentScene->getDefaultCamera();
	camera->setPositionX(heroNode->getPositionX());
	camera->setPositionY(heroNode->getPositionY());

	camera->addComponent(CameraFollowing::create(heroNode));
	heroNode->setPosition(playerSpawnPoint);
	heroNode->setGlobalZOrder(1);

	ItemManageMentSystem::getInstance()->initHeroNode(heroNode);
}

PlayerNode* GameSystem::getHeroNode(){
	return heroNode;
}

void GameSystem::setState(GameState state){
	this->state = state;
	switch (state) {
	case GameState::PLAYING: case GameState::TIMESTOP:
		currentScene->getPhysicsWorld()->setSpeed(1);
		break;
	case GameState::FAILED:
		currentScene->getPhysicsWorld()->setSpeed(0);
		((SceneIngame*)currentScene)->showFailedDialog();
		break;
	default:
		currentScene->getPhysicsWorld()->setSpeed(0);
		break;

	}
}

GameState GameSystem::getState(){
	return this->state;
}

bool GameSystem::isStatePlaying(){
	return this->state == GameState::PLAYING;
}

bool GameSystem::isStateTimeStop()
{
	return this->state == GameState::TIMESTOP;
}
