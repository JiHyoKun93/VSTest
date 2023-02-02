#include "stdafx.h"
#include "CameraFollowing.h"

CameraFollowing* CameraFollowing::create(Node* followingTarget){
	auto ret = new CameraFollowing();
	if (ret && ret->init(followingTarget)) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool CameraFollowing::init(Node* followingTarget){
	if (!Component::init()) return false;

	this->target = followingTarget;

	return true;
}

void CameraFollowing::onAdd(){
	Component::onAdd();
	this->owner = getOwner();

}

void CameraFollowing::update(float dt){
	if (owner == nullptr) return;
	if (target == nullptr) return;

	owner->setPosition(target->getPosition());
}
