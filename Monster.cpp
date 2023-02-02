#include "stdafx.h"
#include "Monster.h"
#include "Environment.h"

Monster* Monster::create(){
	auto ret = new Monster();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool Monster::init() {
	if (!UnitNode::init()) return false;

	spr = makeSpriteMonster(1);
	addChild(spr);

	return true;
}
