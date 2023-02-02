#ifndef __ENVIRONMENT_H__
#define __ENVIRONMENT_H__

#include "stdafx.h"

#ifdef COCOS2D

#include "Exlayout.h"

#define BIND_CLICK(FUNCNAME) std::bind(&FUNCNAME, this, std::placeholders::_1)

#define DEBUG_BACKGROUND_COLOR false
#define DEBUG_PHYSICS_DRAW true

#define FONT_DEFUALT "fonts/NotoSansKR-Medium.otf"

#define TAG_OPTIONS_SOUND 0
#define TAG_OPTIONS_MUSIC 1
#define TAG_OPTIONS_VFX 2
#define TAG_OPTIONS_JOUSTICK 3
#define TAG_OPTIONS_DAMAGE_NUMBERS 4
#define TAG_OPTIONS_PERFOMANCE_MODE 5
#define TAG_OPTIONS_FULLSCREEN 6

#define BASIC_MOVEMENT_SPEED 200
#define BASIC_MOVEMENT_SPEED_MONSTER 100


// P : 00000000000000000000000000000001
// M : 00000000000000000000000000000011
// B : 00000000000000000000000000000010
// I : 00000000000000000000000000000101

#define BITMASK_CONTACT_PLAYER 1 // 밑에껀 다른 방법
#define BITMASK_CONTACT_MONSTER 3 // 1 & (1<<1)
#define BITMASK_CONTACT_BULLET 2 // 1 << 1
#define BITMASK_CONTACT_ITEM 5

#define BITMASK_COLLISION_PLAYER 1
#define BITMASK_COLLISION_MONSTER 3
#define BITMASK_COLLISION_BULLET 2
#define BITMASK_COLLISION_ITEM 5

#define BASIC_MAGNET_RADIUS 3

#define CHARACTOR_SHEET_FILE_NAME "res/map/0x72_DungeonTilesetII_v1.4.png"

#define CHECK_BITMASK(T, A, B, BITMASK) if(A->getCollisionBitmask() == BITMASK) T = A; if(B->getCollisionBitmask() == BITMASK) T = B;

#define ITEM_CAPACITY 10

class Hero;

typedef EventKeyboard::KeyCode Key;
typedef RelativeLayoutParameter::RelativeAlign Align;

//Vec2 getPosByViewprot(const Vec2& offset);

Button* createButtonBlue(const Size& size, const std::string& text, const Vec2& position = Vec2::ZERO);
Button* createButtonRed(const Size& size, const std::string& text, const Vec2& position = Vec2::ZERO);
Button* createButtonGreen(const Size& size, const std::string& text, const Vec2& position = Vec2::ZERO);

Widget* createDummy(const Size& size, Align align, const std::string& dummyRelativeName);
ExLayout* createLayout(const Size& size, const Vec2& position = Vec2::ZERO);
ListView* createListView(const Size& size, const Vec2& position);

Widget* setRelativeParameter(Widget* widget, Align align, const std::string& relativeName="", const std::string& relativeTo="", const Margin& margin = Margin::ZERO);

void addTitleToSubLayout(ExLayout* subLayout, const std::string& str);

ExLayout* createSliderWidgetLayout(const std::string& title, const Size& layoutSize, float defaultValue, const std::function<void(float)>& callback = nullptr);
ExLayout* createCheckBoxWidgetLayout(const std::string& title, const Size& layoutSize,
	bool defaultValue, const std::function<void(bool)>& callback = nullptr);
ExLayout* createCharacterSelectItem(Hero* hero, const Size& size, const std::function<void(bool)>& callback);


void setFloat(int tag, float value);
float getFloat(int tag);

void setBool(int tag, bool value);
bool getBool(int tag);

PhysicsBody* checkBitmask(PhysicsBody* a, PhysicsBody* b, int BITMASK);

void setBitmaskMonster(PhysicsBody * body);
void setBitmaskItem(PhysicsBody * body);
void setBitmaskPlayer(PhysicsBody * body);

Sprite* getSprite(const char* sheetFile, const Vec2 & origin, const Size & size);
Animate* getAnimate(const char* sheetFile, const Vec2 & origin, const Size & size, int animationCount, float delayPerUnit);

Sprite* makeSpritePlayer();
Sprite* makeSpriteMonster(int index);
Sprite* makeSpriteBoss();

TMXTiledMap* createMap(int stageIndex);

#endif //COCOS2D

// 가챠게임에 모두 들어가는 함수 랜덤함수임
float throwDice(float max);
int throwDice(const std::vector<float>& weight_array);
std::vector<int> throwDiceSequence(const std::vector<float>& weight_array, int throwCount, bool allowDuplicate);

class PositionComponent : public Component {
	std::string key;

public:
	static void loadDocument();
	static PositionComponent* create(const std::string& key);
	virtual bool init(const std::string& key);
	virtual void update(float dt);
};


#endif
