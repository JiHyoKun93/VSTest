#ifndef __CAMERA_FOLLOWING_H__
#define __CAMERA_FOLLOWING_H__

#include "stdafx.h"

class CameraFollowing : public Component {
	Node* owner = nullptr;
	Node* target = nullptr;

public:
	static CameraFollowing* create(Node* followingTarget);

	virtual bool init(Node* followingTarget);
	virtual void onAdd();

	void update(float dt);
};

#endif // !__CAMERA_FOLLOWING_H__
