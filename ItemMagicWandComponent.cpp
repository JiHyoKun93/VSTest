#include "stdafx.h"
#include "ItemMagicWandComponent.h"
#include "Bullet.h"
#include "Monster.h"
#include "ItemManagementSystem.h"


ItemMagicWandComponent* ItemMagicWandComponent::create() {
	auto ret = new ItemMagicWandComponent();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool ItemMagicWandComponent::init() {
	if (!ItemBaseComponent::init()) return false;
	setName("MagicWand");
	baseSize = Size(10, 10);
	baseDamage = 30;
	return true;
}

void ItemMagicWandComponent::update(float dt) {
	if (!system->isStatePlaying()) return;
	if (ItemManageMentSystem::getInstance()->getItemInfo(id)->level == 0) return;
	
	realCooldown = baseCooldown * hero->getCooldown();

	cooldown -= dt;
	if (cooldown <= 0.0f) {
		cooldown = realCooldown;

		for (int i = 0; i < hero->getAmount() + baseAmount; i++) {
			// fire magic

			CallFunc* cf = CallFunc::create([=]() {
				Vec2 pos = owner->getPosition();

				BulletNode* bullet = BulletNode::create();
				//bullet->setPosition(pos + Vec2(owner->getFacingDirection().x < 0 ? -100 : 100 * pow(-1, i), i * 20));
				bullet->isPiercing = false;
				bullet->setPosition(pos);
				auto body = PhysicsBody::createBox(baseSize * hero->getArea());
				body->setRotationEnable(false);
				body->setGravityEnable(false);
				body->setCategoryBitmask(BITMASK_COLLISION_BULLET);
				body->setContactTestBitmask(BITMASK_CONTACT_BULLET);
				body->setCollisionBitmask(BITMASK_COLLISION_BULLET);
				body->setDynamic(false);
				bullet->addComponent(body);

				Monster* nearest = system->getNearestMonster();
				
				if (nearest == nullptr) return;
				body->setVelocity((nearest->getPosition() - owner->getPosition()).getNormalized() * 200);

				bullet->runAction(Sequence::create(DelayTime::create(5.0f), RemoveSelf::create(), nullptr));
				bullet->damage = baseDamage * hero->getMight();

				system->getCurrentScene()->addChild(bullet);
				});
			owner->runAction(Sequence::create(DelayTime::create(i * 0.025), cf, nullptr));

		}
	}
}
