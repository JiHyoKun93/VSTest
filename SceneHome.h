#ifndef __SCENE_HOME_H__
#define __SCENE_HOME_H__

#include "stdafx.h"
#include "ExScene.h"
#include "Environment.h"
#include "Exlayout.h"
#include "Hero.h"
#include "SceneIngame.h"
#include "GameSystem.h"

class SceneHome : public ExScene {
private:
	GameSystem* system;

	int selectedHeroIndex;
	Hero* selectedHero;

	Button* btnExit = nullptr;
	Button* btnOption = nullptr;
	Button* btnStart = nullptr;
	Button* btnCollection = nullptr;
	Button* btnEnchant = nullptr;
	Button* btnAchievement = nullptr;
	Button* btnCredit = nullptr;
	Button* btnBack = nullptr;
	Button* btnConfirmGameStart = nullptr;

	ExLayout* lTop = nullptr;
	ExLayout* lMain = nullptr;
	ExLayout* lOption = nullptr;
	ExLayout* lAchievement = nullptr;
	ExLayout* lStart = nullptr;
	ExLayout* lStageSelection = nullptr;
	ExLayout* lEnchant = nullptr;
	ExLayout* lCredit = nullptr;
	ExLayout* lCollection = nullptr;

	Sprite* sprBackground = nullptr;
public:
	static SceneHome* create();
	virtual bool init();

	void createOptionLayout();
	void createStartLayout();
	void createEnchantLayout();
	void createAchievementLayout();
	void createCreditLayout();
	void createCollectionLayout();
	void createStageSelectionLayout();

	void onClickButton(Ref* r);
	
	virtual void inputMove(const Vec2& direction) override;
};

#endif
