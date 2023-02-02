#ifndef __GAME_SYSTEM_H__
#define __GAME_SYSTEM_H__

#include "stdafx.h"
#include "ExScene.h"
#include "Hero.h"
#include "Unit.h"
#include "Monster.h"
#include "PlayerNode.h"
#include "Environment.h"


// �̱��� ������

// �ð�, ų, ����ġ , ���
// �ð��� �Ҷ� float �� �ϸ� ���ӿ����� delta time ���
// long long �� ���� c++�� std ũ�γ� ���

class GameData;
class SoundSystem;
class GameEventHandling;

enum class GameState {
	READY, PLAYING, VICTORY, FAILED, PAUSED, TIMESTOP
};

typedef EventKeyboard::KeyCode Key;

class GameSystem {
private:
	friend class GameEventHandling;
	Vec2 playerSpawnPoint = Vec2::ZERO;

	GameSystem();
	GameData* data = nullptr;
	GameEventHandling* evt = nullptr;
	SoundSystem* sound = nullptr;

	GameState state = GameState::READY;

	Hero* hero;

	int heroIndex;

	// == �������� �Ӽ�
	int stageNumber;
	float timeLimit; // �ʴ���

	ExScene* currentScene;
	Node* ingameMonsterNode;
	Node* ingameExpNode;
	Node* ingameItemNode;

	Vec2 moveVector;

	PlayerNode* heroNode;

	int monsterSize = 0;

	Vec2 playerTilePos;

public:
	static GameSystem* getInstance();

	double calcExpFomular(int level);
	double calcExpSheet(int level);

	void setHero(Hero* value);
	void setHeroIndex(int index);

	Hero* getHero();
	int getHeroIndex();

	void stageStart(int stageNumber, float timeLimitsec);
	void stageFailed();
	void stageVictory();
	void stagePause();
	void stageResume();

	GameState getGameState();

	Monster* getNearestMonster();

	ExScene* getCurrentScene();
	void setCurrentScene(ExScene* scene);

	void logicIngame(float dt);
	void logicTimer(float dt);

	void spawnMonster();

	void dropExpItemAtPosition(const Vec2& position, float expValue);
	void dropGoldItemAtPosition(const Vec2& position, float expValue);
	void dropChickenItemAtPosition(const Vec2& position, float expValue);

	bool onContactBegin(PhysicsContact& contact);
	bool onContactSeparate(PhysicsContact& contact);

	void onContactBulletAndMonster(PhysicsBody* bullet, PhysicsBody* monster);
	void onContactMosterAndPlayer(PhysicsBody* monster, PhysicsBody* player);
	void onContactItemAndPlayer(PhysicsBody* item, PhysicsBody* player);

	void addPlayerExp(double exp);

	void setPlayerSpawnPoint(const Vec2& pos);
	void createHeroInCurrentScene();
	
	PlayerNode* getHeroNode();

	void setState(GameState state);
	GameState getState();
	bool isStatePlaying();
	bool isStateTimeStop();

};

#endif 
