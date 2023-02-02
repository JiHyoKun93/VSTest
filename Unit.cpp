#include "stdafx.h"
#include "Unit.h"

UnitNode* UnitNode::create(){
	auto ret = new UnitNode();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool UnitNode::init() {
	if (!Node::init()) return false;

	return true;
}

void UnitNode::setFacingDirection(const Vec2& dir){
	this->facingDirection = dir;
}

const Vec2& UnitNode::getFacingDirection() {
	// // O: insert return statement here
	return this->facingDirection;
}

float UnitNode::getHp(){
	return hp;
}

void UnitNode::setHp(float hp){
	this->hp = hp;
}

void UnitNode::addHp(float value){
	setHp(getHp() + value);
}

void UnitNode::setMaxHp(float maxHp){
	this->maxHp = maxHp;
}
