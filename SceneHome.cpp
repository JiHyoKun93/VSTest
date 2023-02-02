#include "stdafx.h"
#include "SceneHome.h"
#include "xlang.h"

SceneHome* SceneHome::create() {
	auto ret = new SceneHome();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool SceneHome::init() {
	if (!ExScene::init()) return false;

	system = GameSystem::getInstance();
	setName("SceneHome");
	system->setCurrentScene(this);
	// 화면을 가져오는거( 핸드폰 화면 같은거?)
	Rect area = Director::getInstance()->getSafeAreaRect();

	// 보이는 화면의 왼쪽아래 0,0 = VisibleOrigin
	// 보이는 화면의 사이즈 0,0 ~ ?,? 까지 = VisibleSize
	Vec2 vo = Director::getInstance()->getVisibleOrigin();
	Size vs = Director::getInstance()->getVisibleSize();

	// Layout 은 기본적으로 앵커포인트가 0,0
	addChild(lTop = createLayout(Size(area.size.width, 100), Vec2(0, area.size.height - 100)));
	lTop->setLayoutType(Layout::Type::RELATIVE);
	btnExit = createButtonRed(Size(200, 50), getString("Exit"));
	btnOption = createButtonBlue(Size(200, 50), getString("Option"));
	btnBack = createButtonRed(Size(200, 50), getString("Back"));

	btnStart = createButtonBlue(Size(200, 50), getString("Start"));
	btnEnchant = createButtonGreen(Size(200, 50), getString("Enchant"));
	btnCollection = createButtonBlue(Size(200, 50), getString("Collection"));
	btnAchievement = createButtonBlue(Size(200, 50), getString("Achievement"));
	btnCredit = createButtonBlue(Size(200, 50), getString("Credit"));

	lTop->addChild(createDummy(Size(200, 0), Align::CENTER_IN_PARENT, "Dummy"));

	lTop->addChildButton(setRelativeParameter(btnExit, Align::LOCATION_LEFT_OF_CENTER, "exit", "Dummy"), BIND_CLICK(SceneHome::onClickButton));

	lTop->addChildButton(setRelativeParameter(btnOption, Align::LOCATION_RIGHT_OF_CENTER, "option", "Dummy"), BIND_CLICK(SceneHome::onClickButton));
	lTop->addChildButton(setRelativeParameter(btnBack, Align::LOCATION_RIGHT_OF_CENTER, "back", "Dummy"), BIND_CLICK(SceneHome::onClickButton));
	addChild(lMain = createLayout(Size(area.size.width, area.size.height - 100), Vec2(0, 0)));
	
	lMain->setLayoutType(Layout::Type::RELATIVE);
	lMain->addChild(createDummy(Size(0, 50), Align::PARENT_BOTTOM_CENTER_HORIZONTAL, "Dummy"));

	lMain->addChildButton(setRelativeParameter(btnCredit, Align::LOCATION_ABOVE_CENTER, "credit", "Dummy", Margin(0, 0, 0, 50)), BIND_CLICK(SceneHome::onClickButton));

	lMain->addChildButton(setRelativeParameter(btnEnchant, Align::LOCATION_ABOVE_CENTER, "enchant", "credit", Margin(0,0,0,50)), BIND_CLICK(SceneHome::onClickButton));

	lMain->addChildButton(setRelativeParameter(btnStart, Align::LOCATION_ABOVE_CENTER, "start", "enchant", Margin(0, 0, 0, 50)), BIND_CLICK(SceneHome::onClickButton));

	lMain->addChildButton(setRelativeParameter(btnCollection, Align::LOCATION_LEFT_OF_CENTER, "collection", "enchant", Margin(0,0,100,0)), BIND_CLICK(SceneHome::onClickButton));

	lMain->addChildButton(setRelativeParameter(btnAchievement, Align::LOCATION_RIGHT_OF_CENTER, "collection", "enchant", Margin(100, 0, 0, 0)), BIND_CLICK(SceneHome::onClickButton));

	//lMain->setVisible(false);
	createOptionLayout();
	createStartLayout();
	//createEnchantLayout();
	//createAchievementLayout();
	//createCreditLayout();

	lOption->setVisible(false);
	lStart->setVisible(false);
	btnBack->setVisible(false);

	addChild(sprBackground = Sprite::create("res/ui/girs_2.png"), -1);
	sprBackground->addComponent(PositionComponent::create("backgroundCharacter"));
	

	return true;
}

void SceneHome::createOptionLayout(){
	Rect area = Director::getInstance()->getSafeAreaRect();
	addChild(lOption = createLayout(Size(area.size.width, area.size.height - 100), Vec2(0, 0)));
	lOption->setLayoutType(Layout::Type::RELATIVE);

	Size subLayoutSize = Size(800, lOption->getContentSize().height);
	ExLayout* subLayout = createLayout(subLayoutSize, Vec2(0, area.size.width / 2));
	setRelativeParameter(subLayout, Align::CENTER_IN_PARENT, "Option", "");
	lOption->addChild(subLayout);
	

	subLayout->setLayoutType(Layout::Type::RELATIVE);
	subLayout->setBackGroundImage("res/ui/panel.png");
	subLayout->setBackGroundImageScale9Enabled(true);
	//

	addTitleToSubLayout(subLayout, "Options");

	ListView* lvContent = createListView(Size(800, lOption->getContentSize().height - 100), Vec2::ZERO);
	setRelativeParameter(lvContent, Align::PARENT_BOTTOM_CENTER_HORIZONTAL, "", "");
	subLayout->addChild(lvContent);

	Size itemSize = Size(800, 100);
	lvContent->pushBackCustomItem(createSliderWidgetLayout("Sounds", itemSize, getFloat(TAG_OPTIONS_SOUND), [=](float value)->void {setFloat(TAG_OPTIONS_SOUND, value); })); // TODO
	lvContent->pushBackCustomItem(createSliderWidgetLayout("Music", itemSize, getFloat(TAG_OPTIONS_MUSIC), [=](float value)->void {setFloat(TAG_OPTIONS_MUSIC, value); })); // TODO
	lvContent->pushBackCustomItem(createCheckBoxWidgetLayout("Flashing VFX", itemSize, getBool(TAG_OPTIONS_VFX), [=](bool value)->void {setBool(TAG_OPTIONS_VFX, value); }));
	lvContent->pushBackCustomItem(createCheckBoxWidgetLayout("Visible Joystick", itemSize, getBool(TAG_OPTIONS_JOUSTICK), [=](bool value)->void {setBool(TAG_OPTIONS_JOUSTICK, value); }));
	lvContent->pushBackCustomItem(createCheckBoxWidgetLayout("Damage Numbers", itemSize, getBool(TAG_OPTIONS_DAMAGE_NUMBERS), [=](bool value)->void {setBool(TAG_OPTIONS_DAMAGE_NUMBERS, value); }));
	lvContent->pushBackCustomItem(createCheckBoxWidgetLayout("Performance Mode", itemSize, getBool(TAG_OPTIONS_PERFOMANCE_MODE), [=](bool value)->void {setBool(TAG_OPTIONS_PERFOMANCE_MODE, value); }));
	lvContent->pushBackCustomItem(createCheckBoxWidgetLayout("Fullscreen", itemSize, getBool(TAG_OPTIONS_FULLSCREEN), [=](bool value)->void {setBool(TAG_OPTIONS_FULLSCREEN, value); }));

	lvContent->setBounceEnabled(true);
}

void SceneHome::createStartLayout(){
	Rect area = Director::getInstance()->getSafeAreaRect();
	addChild(lStart = createLayout(Size(area.size.width, area.size.height - 100), Vec2(0, 0)));
	lStart->setLayoutType(Layout::Type::RELATIVE);

	Size subLayoutSize = Size(800, lStart->getContentSize().height);
	ExLayout* subLayout = createLayout(subLayoutSize, Vec2(0, area.size.width / 2));
	setRelativeParameter(subLayout, Align::CENTER_IN_PARENT, "Start", "");
	lStart->addChild(subLayout);
	subLayout->setLayoutType(Layout::Type::RELATIVE);
	subLayout->setBackGroundImage("res/ui/panel_character.png");
	subLayout->setBackGroundImageScale9Enabled(true);

	addTitleToSubLayout(subLayout, "Character Sellection");

	ListView* lvContent = createListView(Size(800, lStart->getContentSize().height - 300), Vec2::ZERO);
	setRelativeParameter(lvContent, Align::PARENT_BOTTOM_CENTER_HORIZONTAL, "", "", Margin(0, 0, 0, 200));
	subLayout->addChild(lvContent);

	ExLayout* bottomLayout = createLayout(Size(800, 200));
	setRelativeParameter(bottomLayout, Align::PARENT_BOTTOM_CENTER_HORIZONTAL);
	subLayout->addChild(bottomLayout);

	Text* tvName = Text::create("samplename samplename", FONT_DEFUALT, 24.0f);
	setRelativeParameter(tvName, Align::PARENT_TOP_LEFT, "", "", Margin(10, 10, 0, 0));
	bottomLayout->addChild(tvName);

	ImageView* ivHero = ImageView::create("res/player-spritemap-v9.png");
	ivHero->setTextureRect(Rect(0, 0, 34, 34));
	setRelativeParameter(ivHero, Align::PARENT_LEFT_BOTTOM, "image", "", Margin(10, 0, 0, 10));
	ivHero->setContentSize(Size(100, 100));
	bottomLayout->addChild(ivHero);

	Text* tvDescription = Text::create("lorem ipsum", FONT_DEFUALT, 24.0f);
	setRelativeParameter(tvDescription, Align::LOCATION_RIGHT_OF_TOPALIGN, "description", "image", Margin(30, 0, 0, 0));
	tvDescription->setTextHorizontalAlignment(TextHAlignment::LEFT); // 정렬해주는 함수 CENTER = text 중앙정렬
	// setTextAreaSize = Text 사이즈? 를 지정해주는것 벗어나지 않게
	tvDescription->setTextAreaSize(Size(400, 80));
	bottomLayout->addChild(tvDescription);

	btnConfirmGameStart = createButtonGreen(Size(200, 50), "Start");
	setRelativeParameter(btnConfirmGameStart, Align::PARENT_RIGHT_BOTTOM, "btnConfirm", "", Margin(0, 0, 20, 20));
	bottomLayout->addChildButton(btnConfirmGameStart, BIND_CLICK(SceneHome::onClickButton));

	int count = 0;
	for (int i = 0; i < (MAX_HEROS-1) / 4 + 1; i++) {
		ExLayout* line = createLayout(Size(800, 200));
		line->setLayoutType(Layout::Type::HORIZONTAL);
		for (int k = count; k < MIN(count + 4, MAX_HEROS); k++) {
			line->addChild(createCharacterSelectItem(Hero::getHeroByIndex(k), Size(200, 200), [=](bool isEnabled) {
				// TODO: 클릭시 프레임 선택 스프라이트 삽입
				if (isEnabled) {
					selectedHeroIndex = k;
					selectedHero = Hero::getHeroByIndex(selectedHeroIndex);

					tvName->setString(selectedHero->getFirstName() + " " + selectedHero->getLastName());
					ivHero->loadTexture(selectedHero->getSpriteFrame()->getTexture()->getPath());
					ivHero->setTextureRect(selectedHero->getSpriteFrame()->getRect());
					tvDescription->setString(selectedHero->getDescription());
				}
			}));
		}
		count += 4;
		lvContent->pushBackCustomItem(line);
	}
}

void SceneHome::createEnchantLayout(){
	Rect area = Director::getInstance()->getSafeAreaRect();
	addChild(lEnchant = createLayout(Size(area.size.width, area.size.height - 100), Vec2(0, 0)));
	lEnchant->setLayoutType(Layout::Type::RELATIVE);

	Size subLayoutSize = Size(800, lEnchant->getContentSize().height);
	ExLayout* subLayout = createLayout(subLayoutSize, Vec2(0, area.size.width / 2));
	setRelativeParameter(subLayout, Align::CENTER_IN_PARENT, "Enchant", "");
	lEnchant->addChild(subLayout);


	addTitleToSubLayout(subLayout, "Power Up");


}

void SceneHome::createAchievementLayout(){
	Rect area = Director::getInstance()->getSafeAreaRect();
	addChild(lAchievement = createLayout(Size(area.size.width, area.size.height - 100), Vec2(0, 0)));
	lAchievement->setLayoutType(Layout::Type::RELATIVE);

	Size subLayoutSize = Size(800, lAchievement->getContentSize().height);
	ExLayout* subLayout = createLayout(subLayoutSize, Vec2(0, area.size.width / 2));
	setRelativeParameter(subLayout, Align::CENTER_IN_PARENT, "Achievement", "");
	lAchievement->addChild(subLayout);


	addTitleToSubLayout(subLayout, "Unlocks");


}

void SceneHome::createCreditLayout(){
	Rect area = Director::getInstance()->getSafeAreaRect();
	addChild(lCredit = createLayout(Size(area.size.width, area.size.height - 100), Vec2(0, 0)));
	lCredit->setLayoutType(Layout::Type::RELATIVE);

	Size subLayoutSize = Size(800, lCredit->getContentSize().height);
	ExLayout* subLayout = createLayout(subLayoutSize, Vec2(0, area.size.width / 2));
	setRelativeParameter(subLayout, Align::CENTER_IN_PARENT, "Credit", "");
	lCredit->addChild(subLayout);


	addTitleToSubLayout(subLayout, "Credits");


}

void SceneHome::createCollectionLayout(){
	Rect area = Director::getInstance()->getSafeAreaRect();
	addChild(lCollection = createLayout(Size(area.size.width, area.size.height - 100), Vec2(0, 0)));
	lCollection->setLayoutType(Layout::Type::RELATIVE);

	Size subLayoutSize = Size(800, lCollection->getContentSize().height);
	ExLayout* subLayout = createLayout(subLayoutSize, Vec2(0, area.size.width / 2));
	setRelativeParameter(subLayout, Align::CENTER_IN_PARENT, "Collection", "");
	lCollection->addChild(subLayout);


	addTitleToSubLayout(subLayout, "Collections");
}

void SceneHome::createStageSelectionLayout(){
	Rect area = Director::getInstance()->getSafeAreaRect();
	addChild(lStageSelection = createLayout(Size(area.size.width, area.size.height - 100), Vec2(0, 0)));
	lStageSelection->setLayoutType(Layout::Type::RELATIVE);

	Size subLayoutSize = Size(800, lStageSelection->getContentSize().height);
	ExLayout* subLayout = createLayout(subLayoutSize, Vec2(0, area.size.width / 2));
	setRelativeParameter(subLayout, Align::CENTER_IN_PARENT, "Stage", "");
	lStageSelection->addChild(subLayout);


	addTitleToSubLayout(subLayout, "Stage");

}

void SceneHome::onClickButton(Ref* r){
	if (r == btnExit) {
		Director::getInstance()->end();
	}
	if (r == btnOption) {
		lMain->setVisible(false);
		lOption->setVisible(true);
		btnBack->setVisible(true);
	}
	if (r == btnStart) {
		lMain->setVisible(false);
		lStart->setVisible(true);
		btnBack->setVisible(true);
	}
	if (r == btnCollection);
	if (r == btnAchievement);
	if (r == btnCredit);
	if (r == btnEnchant);

	if (r == btnBack) {
		btnBack->setVisible(false);
		lMain->setVisible(true);
		if (lOption && lOption->isVisible()) {
			lOption->setVisible(false);
		}
		if (lStart && lStart->isVisible()) {
			lStart->setVisible(false);
		}
		if (lStageSelection && lStageSelection->isVisible()) {
			lStageSelection->setVisible(false);
		}
		if (lCollection && lCollection->isVisible()) {
			lCollection->setVisible(false);
		}
		if (lAchievement && lAchievement->isVisible()) {
			lAchievement->setVisible(false);
		}
		if (lCredit && lCredit->isVisible()) {
			lCredit->setVisible(false);
		}
	}

	if (r == btnConfirmGameStart) {
		GameSystem::getInstance()->setHero(selectedHero);
		Director::getInstance()->replaceScene(SceneIngame::create());
	}

}

void SceneHome::inputMove(const Vec2& direction){

}
