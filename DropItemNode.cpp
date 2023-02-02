#include "stdafx.h"
#include "DropItemNode.h"

DropItemNode* DropItemNode::create(ItemType type){
	auto ret = new DropItemNode();
	if (ret && ret->init(type)) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool DropItemNode::init(ItemType type){
	if (!UnitNode::init()) return false;
	this->type = type;
	return true;
}

void DropItemNode::onEnter(){
	UnitNode::onEnter();

}

ItemType DropItemNode::getType(){
	return type;
}

void DropItemNode::setValue(float value){
	this->value = value;
}

float DropItemNode::getValue() {
	return this -> value;
}
