#include "stdafx.h"
#include "PlayerNode.h"
#include "ItemLaurelComponent.h"
#include "GameSystem.h"

bool PlayerNode::init(){
	if (!UnitNode::init()) return false;

	schedule(CC_SCHEDULE_SELECTOR(PlayerNode::logic));
	system = GameSystem::getInstance();
	hero = system->getHero();

	sprite = makeSpritePlayer();
	addChild(sprite);

	return true;
}

void PlayerNode::logic(float dt){
	// TODO : �÷��̾�� �������ִ� ���� ���� ����
	if (!system->isStatePlaying()) return;

	if(laurel == nullptr) laurel = (ItemLaurelComponent*)getComponent("Laurel");
	
	if (nearMonsterCounter > 0) {
		float realDamage = MIN(-2 + hero->getArmor(), 0);
		bool isBlocked = (laurel != nullptr) && (laurel->block(realDamage));
		if (isBlocked) return;

		addHp(realDamage);
		if (getHp() <= 0) {
			system->setState(GameState::FAILED);
		}
	}
}
