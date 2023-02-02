#include "stdafx.h"
#include "SceneIngame.h"
#include "xlang.h"
#include "SceneResult.h"
#include "ItemManagementSystem.h"
#include "Environment.h"
#include "SceneHome.h"

SceneIngame* SceneIngame::create() {
	auto ret = new SceneIngame();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool SceneIngame::init() {
	if (!ExScene::initWithPhysics()) return false;
	//initWithPhysics 로 변경해줘야 물리엔진 가능

	initBasicUI();
	initPausedUI();
	initOptionsUI();
	initFailedUI();
	initLevelUpUI();

	layoutUI->setCameraMask((unsigned short)CameraFlag::USER1, true);
	layoutPausedUI->setCameraMask((unsigned short)CameraFlag::USER1, true);
	layoutOptions->setCameraMask((unsigned short)CameraFlag::USER1, true);
	layoutFailed->setCameraMask((unsigned short)CameraFlag::USER1, true);
	layoutLevelUp->setCameraMask((unsigned short)CameraFlag::USER1, true);

	layoutPausedUI->setVisible(false);
	layoutOptions->setVisible(false);
	layoutFailed->setVisible(false);
	layoutLevelUp->setVisible(false);

	return true;
}

void SceneIngame::onEnter(){
	ExScene::onEnter();

#if DEBUG_PHYSICS_DRAW
	getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
#endif

	system->createHeroInCurrentScene();

	Camera* defcam = getDefaultCamera();
	defcam->setCameraFlag(CameraFlag::DEFAULT);
	defcam->setPositionZ(defcam->getPositionZ() - 300);
	// 줌인 하는 방법
	//defcam->runAction(MoveBy::create(5.0f, Vec3(0, 0, -100)));

	Camera* uicam = Camera::create();

	uicam->initDefault();
	addChild(uicam);
	uicam->setPosition(Vec2(0, 0));
	uicam->setCameraFlag(CameraFlag::USER1);

}

void SceneIngame::initBasicUI(){
	system = GameSystem::getInstance();
	setName("SceneIngame");
	system->setCurrentScene(this);

	Rect vp = Director::getInstance()->getSafeAreaRect();

	addChild(layoutUI = createLayout(Size(vp.size)));
	layoutUI->setBackGroundColorType(Layout::BackGroundColorType::NONE);
	layoutUI->setPosition(Vec2(-vp.size.width / 2, -vp.size.height / 2));

	pbExp = LoadingBar::create("res/LoadingBarFile.png");
	pbExp->setDirection(LoadingBar::Direction::LEFT);
	pbExp->setContentSize(Size(vp.size.width, 20));
	pbExp->setScale9Enabled(true);
	setRelativeParameter(pbExp, Align::PARENT_TOP_CENTER_HORIZONTAL, "pbExp", "");

	layoutUI->addChild(pbExp);

	tKills = Text::create("Kills: 0", FONT_DEFUALT, 24.0f);
	setRelativeParameter(tKills, Align::LOCATION_BELOW_RIGHTALIGN, "tKills", "pbExp", Margin(0, 50, 50, 0));
	layoutUI->addChild(tKills);

	tTimer = Text::create("00:00", FONT_DEFUALT, 24.0f);
	setRelativeParameter(tTimer, Align::LOCATION_BELOW_CENTER, "tTimer", "pbExp", Margin(0, 50, 0, 0));
	layoutUI->addChild(tTimer);
}

void SceneIngame::initPausedUI(){
	Rect vp = Director::getInstance()->getSafeAreaRect();
	addChild((layoutPausedUI) = createLayout(Size(vp.size)));
	layoutPausedUI->setPosition(-(Vec2)Director::getInstance()->getOpenGLView()->getDesignResolutionSize() / 2);

	layoutPausedUI->addChild(btnOptions = createButtonBlue(Size(300, 80), getString("Options"), Vec2::ZERO));
	layoutPausedUI->addChild(btnResume = createButtonBlue(Size(350, 100), getString("RESUME"), Vec2::ZERO));

	setRelativeParameter(btnResume, Align::PARENT_RIGHT_BOTTOM, "btnResume", "", Margin(0, 0, 100, 100));
	setRelativeParameter(btnOptions, Align::LOCATION_LEFT_OF_BOTTOMALIGN, "btnOptions", "btnResume", Margin(0, 0, 50, 0));

	layoutPausedUI->addChild(btnHome = createButtonBlue(Size(350, 100), getString("Home"), Vec2::ZERO));
	setRelativeParameter(btnHome, Align::PARENT_RIGHT_BOTTOM, "btnHome", "", Margin(100, 0, 0, 100));

	btnResume->addClickEventListener(BIND_CLICK(SceneIngame::onClickButton));
	btnOptions->addClickEventListener(BIND_CLICK(SceneIngame::onClickButton));
	btnHome->addClickEventListener(BIND_CLICK(SceneIngame::onClickButton));
}

void SceneIngame::initOptionsUI(){
	Rect vp = Director::getInstance()->getSafeAreaRect();
	addChild((layoutOptions) = createLayout(Size(vp.size)));
	layoutOptions->setPosition(-(Vec2)Director::getInstance()->getOpenGLView()->getDesignResolutionSize() / 2);

	layoutOptions->addChild(btnBack = createButtonBlue(Size(350, 100), getString("Failed"), Vec2::ZERO));
	setRelativeParameter(btnBack, Align::PARENT_RIGHT_BOTTOM, "btnFailed", "", Margin(0, 0, 100, 100));

	btnBack->addClickEventListener(BIND_CLICK(SceneIngame::onClickButton));
}

void SceneIngame::initFailedUI(){
	Rect vp = Director::getInstance()->getSafeAreaRect();
	addChild((layoutFailed) = createLayout(Size(vp.size)));
	layoutFailed->setPosition(-(Vec2)Director::getInstance()->getOpenGLView()->getDesignResolutionSize() / 2);

	layoutFailed->addChild(btnFaild = createButtonBlue(Size(350, 100), getString("Back"), Vec2::ZERO));
	setRelativeParameter(btnFaild, Align::PARENT_RIGHT_BOTTOM, "btnBack", "", Margin(0, 0, 100, 100));

	btnFaild->addClickEventListener(BIND_CLICK(SceneIngame::onClickButton));
}

void SceneIngame::initLevelUpUI(){
	Rect vp = Director::getInstance()->getSafeAreaRect();
	addChild((layoutLevelUp) = createLayout(Size(vp.size)));
	layoutLevelUp->setPosition(-(Vec2)Director::getInstance()->getOpenGLView()->getDesignResolutionSize() / 2);
	layoutLevelUp->addChild(tLevelUp = Text::create(getString("Level Up"), FONT_DEFUALT, 48.0f));
	setRelativeParameter(tLevelUp, Align::PARENT_TOP_CENTER_HORIZONTAL, "tLevelUp", "", Margin(0, 50, 0, 0));

	lvLevelUp = createListView(Size(500, 650), Vec2::ZERO);
	layoutLevelUp->addChild(lvLevelUp);
	setRelativeParameter(lvLevelUp, Align::CENTER_IN_PARENT, "lvLevelUp", "");
	
	//Margin = 바깥쪽으로 더 가지는 여백 공간
	//Padding 은 안쪽으로 자식들이 얼마나 쪼그라질것인지
	lvLevelUp->setPadding(25, 120, 10, 10);
	lvLevelUp->setItemsMargin(8);
	
	auto ret = ItemManageMentSystem::getInstance()->gacha();
	
	for (int i = 0; i < 3; i++) {
		auto layout = createLayout(Size(450, 160));
		lvLevelUp->pushBackCustomItem(layout);

		ItemInfo* item = ItemManageMentSystem::getInstance()->getItemInfo(ret[i]);

		Text* tTitle = Text::create(getString(item->name.c_str()), FONT_DEFUALT, 24.0f);
		tTitle->setTextAreaSize(Size(300, 0));
		setRelativeParameter(tTitle, Align::PARENT_TOP_LEFT, "tTitle", "", Margin(100, 10, 0, 0));
		layout->addChild(tTitle);

		Text* tSubTitle = Text::create(getString(item->description.c_str()), FONT_DEFUALT, 18.0f);
		tSubTitle->setTextAreaSize(Size(300, 0));
		setRelativeParameter(tSubTitle, Align::LOCATION_BELOW_LEFTALIGN, "tSubTitle", "tTitle", Margin(0, 20, 0, 0));
		layout->addChild(tSubTitle);

		ImageView* ivIcon = ImageView::create(CHARACTOR_SHEET_FILE_NAME);
		ivIcon->setTextureRect(item->spriteFrame->getRect());
		ivIcon->ignoreContentAdaptWithSize(false);
		ivIcon->setContentSize(Size(50, 50));
		setRelativeParameter(ivIcon, Align::PARENT_TOP_LEFT, "ivIcon", "", Margin(20, 10, 0, 0));
		layout->addChild(ivIcon);
		layout->setTouchEnabled(true);

		layout->addClickEventListener([=](Ref* r)->void {
			item->itemGet();
			layoutLevelUp->setVisible(false);
			GameSystem::getInstance()->setState(GameState::PLAYING);
		});

	}
}

void SceneIngame::inputMove(const Vec2& direction){
	system = GameSystem::getInstance();
	if (system->isStatePlaying()) {
		auto heroNode = system->getHeroNode();
		auto speed = system->getHero()->getSpeed() * BASIC_MOVEMENT_SPEED;
		heroNode->getPhysicsBody()->setVelocity(direction * speed);
	}
	else {
		// 플레이중이 아니라면 메뉴이동을 해줘야함
	}
}

void SceneIngame::showPauseDialog(){
	layoutPausedUI->setVisible(true);
}

void SceneIngame::hidePauseDialog(){
	layoutPausedUI->setVisible(false);
}

void SceneIngame::showOptionsDialog(){
	layoutOptions->setVisible(true);
}

void SceneIngame::hideOptionsDialog(){
	layoutOptions->setVisible(false);
}

void SceneIngame::showFailedDialog(){
	layoutFailed->setVisible(true);
}

void SceneIngame::hideFailedDialog(){
	layoutFailed->setVisible(false);
}

void SceneIngame::showLevelUpDialog(){
	layoutLevelUp->setVisible(true);
}

void SceneIngame::hideLevelUpDialog(){
	layoutLevelUp->setVisible(false);
}

void SceneIngame::setTimerString(const char* str){
	tTimer->setString(str);
}

void SceneIngame::onClickButton(Ref* r){
	if (r == btnOptions) {
		// 옵션 창
		showOptionsDialog();
		hidePauseDialog();
	}
	else if (r == btnResume) {
		// 다시 시작
		system->setState(GameState::PLAYING);
		hidePauseDialog();
	}
	else if (r == btnBack) {
		showPauseDialog();
		hideOptionsDialog();
	}
	else if (r == btnFaild) {
		Director::getInstance()->replaceScene(SceneResult::create());
	}
	else if (r == btnHome) {
		system->setState(GameState::READY);
		Director::getInstance()->replaceScene(SceneHome::create());
	}
}
