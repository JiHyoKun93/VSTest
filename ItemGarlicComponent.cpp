#include "stdafx.h"
#include "ItemGarlicComponent.h"
#include "Bullet.h"
#include "ItemManagementSystem.h"

ItemGarlicComponent* ItemGarlicComponent::create() {
	auto ret = new ItemGarlicComponent();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool ItemGarlicComponent::init() {
	if (!ItemBaseComponent::init()) return false;
	setName("Garlic");
	
	return true;
}

void ItemGarlicComponent::onAdd(){
	ItemBaseComponent::onAdd();

	baseSize.width = 100;
	baseDamage = 500;
}


void ItemGarlicComponent::update(float dt) {
	if (!system->isStatePlaying()) return;
	if (ItemManageMentSystem::getInstance()->getItemInfo(id)->level == 0) return;
	// 주기적으로 Player의 cooldown을 계산해주는것
	realCooldown = baseCooldown * hero->getCooldown();

	cooldown -= dt;
	if (cooldown <= 0.0f) {
		cooldown = realCooldown;

			// fire magic

			CallFunc* cf = CallFunc::create([=]() {
				Vec2 pos = owner->getPosition();

				BulletNode* bullet = BulletNode::create();
				bullet->isPiercing = true;
				bullet->setPosition(pos + Vec2(owner->getFacingDirection()));
				auto body = PhysicsBody::createCircle(baseSize.width);
				body->setRotationEnable(false);
				body->setGravityEnable(false);
				body->setCategoryBitmask(BITMASK_COLLISION_BULLET);
				body->setContactTestBitmask(BITMASK_CONTACT_BULLET);
				body->setCollisionBitmask(BITMASK_COLLISION_BULLET);
				body->setDynamic(false);
				bullet->addComponent(body);
				bullet->runAction(Sequence::create(DelayTime::create(0.1f), RemoveSelf::create(), nullptr));
				bullet->damage = baseDamage * hero->getMight();

				system->getCurrentScene()->addChild(bullet);
				});
			owner->runAction(Sequence::create(cf, nullptr));
	}
}
