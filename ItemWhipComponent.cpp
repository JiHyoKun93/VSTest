#include "stdafx.h"
#include "ItemWhipComponent.h"
#include "Bullet.h"
#include "ItemManagementSystem.h"

ItemWhipComponent* ItemWhipComponent::create(){
	auto ret = new ItemWhipComponent();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool ItemWhipComponent::init(){
	if (!ItemBaseComponent::init()) return false;
	setName("Whip");
	baseCooldown = 1.0f;
	baseSize = Size(300, 50);
	return true;
}

void ItemWhipComponent::update(float dt){
	if (!system->isStatePlaying()) return;
	if (ItemManageMentSystem::getInstance()->getItemInfo(id)->level == 0) return;
	// 주기적으로 Player의 cooldown을 계산해주는것
	realCooldown = baseCooldown * hero->getCooldown();

	cooldown -= dt;
	if (cooldown <= 0.0f) {
		cooldown = realCooldown;

		for (int i = 0; i < hero->getAmount() + baseAmount; i++) {
			// fire magic

			CallFunc* cf = CallFunc::create([=]() {
				Vec2 pos = owner->getPosition();
				
				BulletNode* bullet = BulletNode::create();
				bullet->isPiercing = true;
				bullet->setPosition(pos + Vec2(owner->getFacingDirection().x < 0 ? -100 : 100 * pow(-1, i), i*20));
				auto body = PhysicsBody::createBox(baseSize * hero->getArea());
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
			owner->runAction(Sequence::create(DelayTime::create(i * 0.025), cf, nullptr));
			
		}
	}
}
