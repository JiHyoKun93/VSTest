#ifndef __ITEM_BOOK_COMPONENT_H__
#define __ITEM_BOOK_COMPONENT_H__

#include "stdafx.h"
#include "ItemBaseComponent.h"

class ItemBookComponent : public ItemBaseComponent {
public:
	static ItemBookComponent* create();
	virtual bool init();
	virtual void onAdd() override;

	virtual void update(float dt);
};
#endif // !__ITEM_WHIP_COMPONENT_H__
