#ifndef __ITEM_WHIP_COMPONENT_H__
#define __ITEM_WHIP_COMPONENT_H__

#include "stdafx.h"
#include "ItemBaseComponent.h"

class ItemWhipComponent : public ItemBaseComponent {
public:
	static ItemWhipComponent* create();
	virtual bool init();
	virtual void update(float dt) override;
};
#endif // !__ITEM_WHIP_COMPONENT_H__
