#ifndef __SCENE_INGAME_H__
#define __SCENE_INGAME_H__

#include "stdafx.h"
#include "ExScene.h"
#include "Environment.h"
#include "GameSystem.h"

class SceneIngame : public ExScene {
private:
	GameSystem* system;
	ExLayout* layoutUI;
	ExLayout* layoutPausedUI;
	ExLayout* layoutOptions;
	ExLayout* layoutFailed;
	ExLayout* layoutLevelUp;

	Button* btnOptions;
	Button* btnResume;
	Button* btnBack;
	Button* btnFaild;
	Button* btnHome;

	ListView* lvLevelUp;
	Text* tLevelUp;

public:
	LoadingBar* pbExp;
	Text* tKills;
	Text* tTimer;

	static SceneIngame* create();
	virtual bool init();
	virtual void onEnter();

	void initBasicUI();
	void initPausedUI();
	void initOptionsUI();
	void initFailedUI();
	void initLevelUpUI();

	virtual void inputMove(const Vec2& direction) override;

	void showPauseDialog();
	void hidePauseDialog();
	void showOptionsDialog();
	void hideOptionsDialog();
	void showFailedDialog();
	void hideFailedDialog();
	void showLevelUpDialog();
	void hideLevelUpDialog();

	void setTimerString(const char* str);

	void onClickButton(Ref* r);

};

#endif
