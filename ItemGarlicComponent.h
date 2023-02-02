#ifndef __ITEM_GARLIC_COMPONENT_H__
#define __ITEM_GARLIC_COMPONENT_H__

#include "stdafx.h"
#include "ItemBaseComponent.h"

class ItemGarlicComponent : public ItemBaseComponent {
public:
	static ItemGarlicComponent* create();
	virtual bool init();

	virtual void onAdd() override;

	virtual void update(float dt);
};
#endif // !__ITEM_WHIP_COMPONENT_H__
