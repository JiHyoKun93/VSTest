#include "stdafx.h"
#include "ItemBookComponent.h"
#include "Bullet.h"
#include "ItemManagementSystem.h"

ItemBookComponent* ItemBookComponent::create() {
	auto ret = new ItemBookComponent();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool ItemBookComponent::init() {
	if (!ItemBaseComponent::init()) return false;

	return true;
}

void ItemBookComponent::onAdd(){
	ItemBaseComponent::onAdd();
	baseCooldown = 5.0f;
	baseSize.width = 25;
	baseSize.height = 25;
	baseDuration = 3.0f;
	baseAmount = 2;
}


void ItemBookComponent::update(float dt) {
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
				bullet->isPiercing = true;
				bullet->setPosition(pos);
				auto body = PhysicsBody::createBox(baseSize * hero->getArea());
				body->setRotationEnable(false);
				body->setGravityEnable(false);
				body->setCategoryBitmask(BITMASK_COLLISION_BULLET);
				body->setContactTestBitmask(BITMASK_CONTACT_BULLET);
				body->setCollisionBitmask(BITMASK_COLLISION_BULLET);
				body->setDynamic(false);
				bullet->addComponent(body);

				float angle = (i / (baseAmount + hero->getAmount())) * (3.141592 * 2);
				float r = baseSize.width * 5;
				bullet->setPosition(Vec2(r * cosf(angle), r * sinf(angle)) + pos);
				
				bullet->angleCount = angle;

				bullet->schedule([=](float dt)->void {
					bullet->angleCount += (dt / (3.141592 * 2)) * 5;
					bullet->setPosition(owner->getPosition() + Vec2(r * cosf(bullet->angleCount), r * sinf(bullet->angleCount)));
				}, "rotation");

				bullet->runAction(Sequence::create(DelayTime::create(baseDuration), RemoveSelf::create(), nullptr));
				bullet->damage = baseDamage * hero->getMight();

				system->getCurrentScene()->addChild(bullet);
				});
			owner->runAction(Sequence::create(cf, nullptr));

		}
	}
}