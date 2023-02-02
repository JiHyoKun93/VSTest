#ifndef __DROP_ITEM_NODE_H__
#define __DROP_ITEM_NODE_H__

#include "stdafx.h"
#include "Unit.h"

enum class ItemType {
	CHICKEN, EXP, GOLD
};

class DropItemNode : public UnitNode {
private:
	ItemType type;
	float value = 1;
public:

	static DropItemNode* create(ItemType type);
	virtual bool init(ItemType type);

	virtual void onEnter();

	ItemType getType();
	void setValue(float value);
	float getValue();

};

#endif // !__DROP_ITEM_MODE_H__
