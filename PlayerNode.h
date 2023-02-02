#ifndef __PLAYER_NODE_H__
#define __PLAYER_NODE_H__

#include "stdafx.h"
#include "Unit.h"
#include "Hero.h"

class GameSystem;
class ItemLaurelComponent;

class PlayerNode : public UnitNode {
public:
	ItemLaurelComponent* laurel;
	Sprite* sprite = nullptr;

	int nearMonsterCounter = 0;
	GameSystem* system;
	Hero* hero;

	CREATE_FUNC(PlayerNode);
	virtual bool init();

	void logic(float dt);
};
#endif // !__PLAYER_NODE_H__
