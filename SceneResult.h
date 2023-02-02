#ifndef __SCENE_RESULT_H__
#define __SCENE_RESULT_H__

#include "stdafx.h"
#include "ExScene.h"
#include "Environment.h"
#include "GameSystem.h"

class SceneResult : public ExScene {
public:

	GameSystem* system;

	static SceneResult* create();
	virtual bool init();

	virtual void inputMove(const Vec2& direction) override;
};

#endif
