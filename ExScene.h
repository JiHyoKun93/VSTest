#ifndef __EX_SCENE_H__
#define __EX_SCENE_H__

#include "stdafx.h"

class ExScene : public Scene {
private:
	TMXTiledMap* map = nullptr;
	Node* mapWrapper = nullptr;
public:
	static ExScene* create();
	virtual bool init() override;

	virtual void inputMove(const Vec2& direction) {};
	virtual void inputFire(int fireButton) {};

	Node* getOrCreateNode(const char* name);
	Node* getOrCreateNodeInMap(const char* name);

	void setMap(TMXTiledMap* map);
	TMXTiledMap* getMap();

	void logicPositionData(float dt);
};
#endif // !__EX_SCENE_H__
