#ifndef __ITEM_MAGIC_WAND_COMPONENT_H__
#define __ITEM_MAGIC_WAND_COMPONENT_H__

#include "stdafx.h"
#include "ItemBaseComponent.h"

class ItemMagicWandComponent : public ItemBaseComponent {
public:
	static ItemMagicWandComponent* create();
	virtual bool init();

	virtual void update(float dt);
};
#endif // !__ITEM_WHIP_COMPONENT_H__
