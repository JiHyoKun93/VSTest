#ifndef __UNIT_H__
#define __UNIT_H__

#include "stdafx.h"

class UnitNode : public Node {
private:
	Vec2 facingDirection;
	float hp = 100;
	float maxHp = 100;
public:

	static UnitNode* create();
	virtual bool init();

	void setFacingDirection(const Vec2& dir);
	const Vec2& getFacingDirection();

	float getHp();
	void setHp(float hp);
	void addHp(float value);
	void setMaxHp(float maxHp);
};
#endif // !__UNIT_H__
