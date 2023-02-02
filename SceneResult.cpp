#include "stdafx.h"
#include "SceneResult.h"
SceneResult* SceneResult::create() {
	auto ret = new SceneResult();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool SceneResult::init() {
	if (!ExScene::init()) return false;
	system = GameSystem::getInstance();
	setName("SceneResult");
	system->setCurrentScene(this);
	return true;
}

void SceneResult::inputMove(const Vec2& direction)
{
}
