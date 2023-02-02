#include "stdafx.h"
#include "ItemBaseComponent.h"

bool ItemBaseComponent::init(){
	if (!Component::init()) return false;
	system = GameSystem::getInstance();
	hero = system->getHero();
	return true;
}

void ItemBaseComponent::onAdd(){
	Component::onAdd();
	owner = (UnitNode*)getOwner();
}
