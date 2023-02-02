#ifndef __BULLET_H__
#define __BULLET_H__

#include "stdafx.h"

class BulletNode : public Node {
private:

public:
	float angleCount = 0;
	float damage = 0;

	static BulletNode* create();
	virtual bool init();

	bool isPiercing = false;

};
#endif // !__BULLET_H__
