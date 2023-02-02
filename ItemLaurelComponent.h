#ifndef __ITEM_LAUREL_COMPONENT_H__
#define __ITEM_LAUREL_COMPONENT_H__

#include "stdafx.h"
#include "ItemBaseComponent.h"


class ItemLaurelComponent : public ItemBaseComponent {
private:
	int baseDefCount = 0;
	float baseInvulnerableTime = 1.0f;

	int defCount = 1;
	float invulnerableTime = 0.0f;
public:
	static ItemLaurelComponent* create();
	virtual bool init();

	virtual void onAdd();

	//true 를 리턴 = 막음
	//false 를 리턴 = 못막음
	bool block(float damage);
	void update(float dt);

};
#endif // !__ITEM_WHIP_COMPONENT_H__
