#ifndef __ITEM_BASE_COMPONENT_H__
#define __ITEM_BASE_COMPONENT_H__

#include "stdafx.h"
#include "Hero.h"
#include "Unit.h"
#include "GameSystem.h"

class ItemBaseComponent : public Component {
protected:
	UnitNode* owner;
	GameSystem* system;

	float baseCooldown = 1.0f;
	float realCooldown = baseCooldown;
	float cooldown = 0.0f;

	Size baseSize = Size(300, 20);

	float baseDamage = 10.0f;
	float baseDuration = 1.0f;
	int baseAmount = 1;

	Hero* hero;
public:
	int id = 0;
	CREATE_FUNC(ItemBaseComponent);

	virtual bool init();
	virtual void onAdd() override;
};
#endif // !__ITEM_BASE_COMPONENT_H__
