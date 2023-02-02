#include "stdafx.h"
#include "ItemLaurelComponent.h"
#include "ItemManagementSystem.h"

ItemLaurelComponent* ItemLaurelComponent::create() {
	auto ret = new ItemLaurelComponent();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool ItemLaurelComponent::init() {
	if (!ItemBaseComponent::init()) return false;
	
	setName("Laurel");

	return true;
}

void ItemLaurelComponent::onAdd(){
	ItemBaseComponent::onAdd();
	baseCooldown = 10;
	realCooldown = baseCooldown;
}

bool ItemLaurelComponent::block(float damage){
	
	if (invulnerableTime > 0) {
		return true;
	}
	else if (defCount > 0) {
		defCount -= 1;
		invulnerableTime = baseInvulnerableTime;
		return true;
	}
	return false;
}

void ItemLaurelComponent::update(float dt){
	if (!system->isStatePlaying()) return;
	if (ItemManageMentSystem::getInstance()->getItemInfo(id)->level == 0) return;
	if (invulnerableTime > 0) {
		invulnerableTime -= dt;
	}
	realCooldown -= dt;
	if (realCooldown <= 0 && defCount < baseDefCount) {
		realCooldown = baseCooldown;
		defCount += 1;
	}
}
