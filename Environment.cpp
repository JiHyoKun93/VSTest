#include "stdafx.h"
#include "Environment.h"
#include "Hero.h"
#include "GameSystem.h"

#ifdef COCOS2D

static std::map<std::string, std::function<void(TMXTiledMap*, const ValueMap&, float x, float y, float width, float height)>> eventFuncs = {

	{"PlayerSpawn", [=](TMXTiledMap* map, const ValueMap& value, float x, float y, float width, float height) {
		GameSystem::getInstance()->setPlayerSpawnPoint(Vec2(x, y));
	}},
	{"gateway", [=](TMXTiledMap* map, ValueMap value, float x, float y, float width, float height) {
		Node* n = Node::create();
		n->setPosition(x + width / 2, y + height / 2);
		PhysicsBody* body = PhysicsBody::createBox(Size(width, height));
		body->setGravityEnable(false);
		n->addComponent(body);
		map->addChild(n);

	}},
	{"gatewayto", [=](TMXTiledMap* map, ValueMap value, float x, float y, float width, float height) {

	}},
	{"potion", [=](TMXTiledMap* map, ValueMap value, float x, float y, float width, float height) {
		int gid = value["gid"].asInt();
		auto tileset = map->getLayer("ground")->getTileSet();
		Rect tileRect = tileset->getRectForGID(gid);
		Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(tileset->_sourceImage);
		Sprite* spr = Sprite::createWithTexture(texture, tileRect);
		map->addChild(spr);
		spr->setGlobalZOrder(99999);
		spr->setPosition(Vec2(x, y));
	}}
};

static Color3B debugBackgroundColor[7] = {
	Color3B(255, 255, 255),
	Color3B(255, 50, 50),
	Color3B(50, 255, 50),
	Color3B(50, 50, 255),
	Color3B(255, 255, 50),
	Color3B(50, 255, 255),
	Color3B(255, 50, 255),
};
static int debugBackgroundCounter = 0;

Button* createButtonBlue(const Size& size, const std::string& text, const Vec2& position) {
	const char* textureName = "res/ui/btn_0.png";
	const char* prssedTextureName = "res/ui/btn_1.png";
	const Color3B titleColor = Color3B::BLACK;
	const float fontSize = 24.0f;

	Button* btn = Button::create(textureName, textureName, textureName);
	btn->setScale9Enabled(true);
	btn->setTitleText(text);
	btn->setTitleColor(titleColor);
	btn->setContentSize(size);
	btn->setPosition(position);
	btn->setTitleFontSize(fontSize);
	btn->getTitleLabel()->enableBold();
	return btn;
}

Button* createButtonRed(const Size& size, const std::string& text, const Vec2& position) {
	const char* textureName = "res/ui/btn_0.png";
	const char* prssedTextureName = "res/ui/btn_1.png";
	const Color3B titleColor = Color3B::BLACK;
	const float fontSize = 24.0f;

	Button* btn = Button::create(textureName, textureName, textureName);
	btn->setScale9Enabled(true);
	btn->setTitleText(text);
	btn->setTitleColor(titleColor);
	btn->setContentSize(size);
	btn->setPosition(position);
	btn->setTitleFontSize(fontSize);
	btn->getTitleLabel()->enableBold();

	return btn;
}

Button* createButtonGreen(const Size& size, const std::string& text, const Vec2& position){
	const char* textureName = "res/ui/btn_0.png";
	const char* prssedTextureName = "res/ui/btn_1.png";
	const Color3B titleColor = Color3B::BLACK;
	const float fontSize = 24.0f;

	Button* btn = Button::create(textureName, textureName, textureName);
	btn->setScale9Enabled(true);
	btn->setTitleText(text);
	btn->setTitleColor(titleColor);
	btn->setContentSize(size);
	btn->setPosition(position);
	btn->setTitleFontSize(fontSize);
	btn->getTitleLabel()->enableBold();

	return btn;
}

Widget* createDummy(const Size& size, Align align, const std::string& dummyRelativeName){
	auto ret = Widget::create();
	ret->setContentSize(size);
	setRelativeParameter(ret, align, dummyRelativeName, "");
	return ret;
}

ExLayout* createLayout(const Size& size, const Vec2& position){
	ExLayout* ret = ExLayout::create();
	ret->setContentSize(size);
	ret->setPosition(position);
	ret->setLayoutType(Layout::Type::RELATIVE);
	// Layout 보이게 만들기(아래)
#if DEBUG_BACKGROUND_COLOR
	ret->setBackGroundColor(debugBackgroundColor[debugBackgroundCounter++ % 7]);
	ret->setBackGroundColorOpacity(80); //투명도 같은거
	ret->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
#endif
	return ret;
}

ListView* createListView(const Size& size, const Vec2& position){
	ListView* list = ListView::create();
	list->setContentSize(size);

#if DEBUG_BACKGROUND_COLOR
	list->setBackGroundColor(debugBackgroundColor[debugBackgroundCounter++ % 7]);
	list->setBackGroundColorOpacity(80); //투명도 같은거
	list->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
#endif
	return list;
}

Widget* setRelativeParameter(Widget* widget, Align align, const std::string& relativeName, const std::string& relativeTo, const Margin& margin){
	auto param = RelativeLayoutParameter::create();
	param->setAlign(align);
	param->setRelativeName(relativeName);
	param->setRelativeToWidgetName(relativeTo);
	param->setMargin(margin);
	widget->setLayoutParameter(param);
	return widget;
}

void addTitleToSubLayout(ExLayout* subLayout, const std::string& str){
	Text* text = Text::create(str, FONT_DEFUALT, 48.0f);
	setRelativeParameter(text, Align::PARENT_TOP_CENTER_HORIZONTAL, "", "", Margin(0, 20, 0, 0));

	subLayout->addChild(text);
}

ExLayout* createSliderWidgetLayout(const std::string& title, const Size& layoutSize, float defaultValue, const std::function<void(float)>& callback) {
	ExLayout* layout = ExLayout::create();
	layout->setContentSize(layoutSize);
	layout->setLayoutType(Layout::Type::RELATIVE);

	Text* titleText = Text::create(title, FONT_DEFUALT, 32.0f);
	setRelativeParameter(titleText, Align::PARENT_LEFT_CENTER_VERTICAL, "", "", Margin(50, 0, 0, 0));
	layout->addChild(titleText);

	Slider* slider = Slider::create();
	slider->loadBarTexture("res/Slider_Back.png");
	slider->loadSlidBallTextures("res/SliderNode_Normal.png", "res/SliderNode_Press.png", "res/SliderNode_Disable.png");
	slider->loadProgressBarTexture("res/Slider_PressBar.png");
	setRelativeParameter(slider, Align::PARENT_RIGHT_CENTER_VERTICAL, "", "", Margin(0, 0, 50, 0));
	slider->setMaxPercent(100);
	layout->addChild(slider);
	slider->setPercent((int)(defaultValue * 100.0f));

	slider->addEventListener([=](Ref*, Slider::EventType e)-> void {
		switch (e) {
		case Slider::EventType::ON_PERCENTAGE_CHANGED: callback((float)slider->getPercent() / 100.0f); break;
		}
	});

	return layout;
}

ExLayout* createCheckBoxWidgetLayout(const std::string& title, const Size& layoutSize, bool defaultValue, const std::function<void(bool)>& callback){
	ExLayout* layout = ExLayout::create();
	layout->setContentSize(layoutSize);
	layout->setLayoutType(Layout::Type::RELATIVE);

	Text* titleText = Text::create(title, FONT_DEFUALT, 32.0f);
	setRelativeParameter(titleText, Align::PARENT_LEFT_CENTER_VERTICAL, "", "", Margin(50, 0, 0, 0));
	layout->addChild(titleText);
	
	CheckBox* cb = CheckBox::create("res/CheckBox_Normal.png",
		"res/CheckBox_Press.png",
		"res/CheckBoxNode_Normal.png",
		"res/CheckBox_Disable.png",
		"res/CheckBoxNode_Disable.png");
	setRelativeParameter(cb, Align::PARENT_RIGHT_CENTER_VERTICAL, "", "", Margin(0, 0, 50, 0));
	layout->addChild(cb);
	cb->setSelected(defaultValue);
	cb->addEventListener([=](Ref*, CheckBox::EventType e)->void {
		callback(e == CheckBox::EventType::SELECTED);

	});

	return layout;
}

ExLayout* createCharacterSelectItem(Hero* hero, const Size& size, const std::function<void(bool)>& callback){
	ExLayout* parent = createLayout(size);
	parent->setLayoutType(Layout::Type::RELATIVE);

	ExLayout* layout = createLayout(size - Size(10,10));
	setRelativeParameter(layout, Align::CENTER_IN_PARENT, "", "");
	layout->setLayoutType(Layout::Type::RELATIVE);
	//layout->setBackGroundImage();
	//layout->setBackGroundImageScale9Enabled(true);

	Text* tName = Text::create(hero->getFirstName(), FONT_DEFUALT, 32.0f);
	setRelativeParameter(tName, Align::PARENT_TOP_CENTER_HORIZONTAL, "", "", Margin(0, 10, 0, 0));
	layout->addChild(tName);

	ImageView* imageView = ImageView::create(hero->getSpriteFrame()->getTexture()->getPath());
	imageView->setTextureRect(hero->getSpriteFrame()->getRect());
	layout->addChild(imageView);
	setRelativeParameter(imageView, Align::PARENT_BOTTOM_CENTER_HORIZONTAL);

	layout->addClickEventListener([=](Ref* r)->void {
		// 여기서 클릭시 어떤 효과가 나타나는지 처리를 해줄겁니다.
		parent->arg0 = !parent->arg0;
		callback(parent->arg0);
	});
	layout->setTouchEnabled(true);

	parent->addChild(layout);

	return parent;
}

static float floatData[128] = { 0, };
static bool floatRead[128] = { 0, };

static bool boolData[128] = { 0, };
static bool boolRead[128] = { 0, };

void setFloat(int tag, float value){
	floatData[tag] = value;
	char key[32];
	sprintf(key, "float-%d", tag);
	UserDefault::getInstance()->setFloatForKey(key, value);
	UserDefault::getInstance()->flush();
	floatRead[tag] = true;
}

void setBool(int tag, bool value) {
	boolData[tag] = value;
	char key[32];
	sprintf(key, "bool-%d", tag);
	UserDefault::getInstance()->setBoolForKey(key, value);
	UserDefault::getInstance()->flush();
	boolRead[tag] = true;
}

float getFloat(int tag){
	if (!floatRead[tag]) {
		char key[32];
		sprintf(key, "float-%d", tag);
		floatData[tag] = UserDefault::getInstance()->getFloatForKey(key, 0);
		floatRead[tag] = true;
	}
	return floatData[tag];
}

bool getBool(int tag){
	if (!boolRead[tag]) {
		char key[32];
		sprintf(key, "bool-%d", tag);
		boolData[tag] = UserDefault::getInstance()->getBoolForKey(key, 0);
		boolRead[tag] = true;
	}
	return boolData[tag];
}

PhysicsBody* checkBitmask(PhysicsBody* a, PhysicsBody* b, int BITMASK){
	if (a->getCollisionBitmask() == BITMASK) return a;
	else if (b->getCollisionBitmask() == BITMASK) return b;
	else return nullptr;
}

Sprite* getSprite(const char* sheetFile, const Vec2& origin, const Size& size){
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(sheetFile);
	texture->setAliasTexParameters();
	Sprite* spr = Sprite::createWithTexture(texture, Rect(origin, size));
	return spr;
}

Animate* getAnimate(const char* sheetFile, const Vec2& origin, const Size& size, int animationCount, float delayPerUnit) {
	Texture2D* texture = Director::getInstance()->getTextureCache()->addImage(sheetFile);
	texture->setAliasTexParameters();
	Animation* animation = Animation::create();
	for (int i = 0; i < animationCount; i++) {
		animation->addSpriteFrameWithTexture(texture, Rect(origin + Vec2(size.width * i, 0), size));
	}
	animation->setDelayPerUnit(delayPerUnit);
	Animate* animate = Animate::create(animation);

	return animate;
}

Sprite* makeSpritePlayer(){
	auto sprite = getSprite(CHARACTOR_SHEET_FILE_NAME, Vec2(128, 0), Size(16, 32));
	sprite->setScale(1.0);
	sprite->setPosition(Vec2(0, 20));

	sprite->runAction(RepeatForever::create(getAnimate(CHARACTOR_SHEET_FILE_NAME, Vec2(128, 0), Size(16, 32), 4, 0.1f)));

	return sprite;
}

Sprite* makeSpriteMonster(int index){
	auto sprite = getSprite(CHARACTOR_SHEET_FILE_NAME, Vec2(368, 16 * index), Size(16, 16));
	sprite->setScale(1.0);
	sprite->setPosition(Vec2(0, 10));

	sprite->runAction(RepeatForever::create(getAnimate(CHARACTOR_SHEET_FILE_NAME, Vec2(368, 16 * index), Size(16, 16), 4, 0.1f)));

	return sprite;
}

Sprite* makeSpriteBoss(){

	return nullptr;
}

TMXTiledMap* createMap(int stageIndex){
	char line[100];
	sprintf(line, "res/map/stage%d.tmx", stageIndex);
	auto ret = TMXTiledMap::create(line);
	ret->setScale(1.0);
	// 내가 테스트 해보려고 추가한것
	auto a = ret->getLayer("map");
	a->setGlobalZOrder(-1.0);
	//
	TMXObjectGroup* eventRect = ret->getObjectGroup("eventRect");
	auto objs = eventRect->getObjects();
	for (auto obj : objs) {
		auto valuemap = obj.asValueMap();
		std::string name = valuemap["name"].asString();

		if (eventFuncs.count(name) == 0) continue;

		float x = valuemap["x"].asFloat();
		float y = valuemap["y"].asFloat();
		float width = valuemap["width"].asFloat();
		float height = valuemap["height"].asFloat();

		//eventFuncs[name](ret, valuemap, x, y, width, height);
	}

	/*auto layer = ret->getLayer("frontWall");
	Size mapSize = ret->getMapSize();
	for (int i = 0; i < mapSize.width; i++) {
		for (int k = 0; k < mapSize.height; k++) {
			auto tile = layer->getTileAt(Vec2(i, k));
			tile->setGlobalZOrder(k);
		}
	}*/

	return ret;
}

#endif

float throwDice(float max){
	// 방법1 
	//return RandomHelper::random_int<int>(0, sides);
	// 방법2 가장 원시적인 방법이지만 좋지는 않다.
	//int intpart = rand() % (int)max;
	// 방법 3 0~1 사이의 소수점수 fraction 을 구해서 max를 곱해버림
	const int MOD = 1000;
	float fraction = (rand() % MOD);
	fraction = fraction / MOD;

	return max * fraction;
}

int throwDice(const std::vector<float>& weight_array){
	int sides = weight_array.size();

	// total 합 구하기
	float total = 0;
	for (int i = 0; i < sides; i++) {
		total += weight_array[i];
	}

	// 노멀라이즈된 값 만들기
	float weight_sum = 0;
	std::vector<float> normalized;
	for (int i = 0; i < sides; i++) {
		weight_sum += weight_array[i] / total;
		normalized.push_back(weight_sum);
	}

	float point = throwDice(weight_sum);
	int ret = -1;
	for (int i = 0; i < sides; i++) {
		if (point < normalized[i]) {
			ret = i;
			break;
		}
	}

	return ret;
}

std::vector<int> throwDiceSequence(const std::vector<float>& weight_array, int throwCount, bool allowDuplicate){
	std::vector<int> ret;

	if (allowDuplicate) {
		for (int i = 0; i < throwCount; i++) {
			// 중복이 허용될 경우
			ret.push_back(throwDice(weight_array));
		}
	}
	// 중복 X
	else {
		std::vector<float> temp_array = weight_array;
		for (int i = 0; i < throwCount; i++) {
			int result = throwDice(temp_array);
			temp_array[result] = 0;
			ret.push_back(result);
		}
	}

	return ret;
}


static rapidjson::Document d;

void PositionComponent::loadDocument(){
	auto path = FileUtils::getInstance()->getWritablePath();

	std::string str = FileUtils::getInstance()->getStringFromFile(path + "position.json");
	d.Parse(str.c_str());
}

PositionComponent* PositionComponent::create(const std::string& key){
	auto ret = new PositionComponent();
	if (ret && ret->init(key)) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool PositionComponent::init(const std::string& key){
	if (!Component::init()) return false;
	this->key = key;
	setName("Position");

	return true;
}

void PositionComponent::update(float dt){
	if (!d.HasMember(key.c_str())) return;
	if (!d[key.c_str()].IsArray()) return;

	float x = 0;
	float y = 0;
	if (d[key.c_str()][0].IsFalse()) x = d[key.c_str()][0].GetFloat();
	if (d[key.c_str()][1].IsFalse()) y = d[key.c_str()][1].GetFloat();
	auto ret = getOwner();
	getOwner()->setPosition(Vec2(x, y));
}
