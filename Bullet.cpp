#include "stdafx.h"
#include "Bullet.h"

BulletNode* BulletNode::create(){
	auto ret = new BulletNode();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool BulletNode::init(){
	if (!Node::init()) return false;

	return true;
}
