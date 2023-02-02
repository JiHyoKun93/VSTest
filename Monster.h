#ifndef __MONSTER_H__
#define __MONSTER_H__

#include "stdafx.h"
#include "Unit.h"

class Monster : public UnitNode {
private:
	Sprite* spr = nullptr;
public:
	float atk = 1;
	static Monster* create();
	virtual bool init();

};
#endif // !__MONSTER_H__
