#ifndef __ITEM_MANAGEMENT_SYSTEM_H__
#define __ITEM_MANAGEMENT_SYSTEM_H__

#include "stdafx.h"
#include "ItemBaseComponent.h"

class ItemInfo {
public:
	std::string name;
	std::string description;
	int level = 0;
	int id;
	int base_weight;
	int weight;
	ItemBaseComponent* component;

	SpriteFrame* spriteFrame;

	std::function<void()> itemGet = 0;
};

class ItemManageMentSystem {
	ItemInfo* items[10];
	ItemManageMentSystem();
public:
	static ItemManageMentSystem* getInstance();
	void initInfo();
	void initHeroNode(UnitNode* hero);

	std::vector<int> gacha();
	ItemInfo* getItemInfo(int index);
};

#endif // !__ITEM_MANAGEMENT_SYSTEM_H__
