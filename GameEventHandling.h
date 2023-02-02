#ifndef __GAME_EVENT_HANDLING_H__
#define __GAME_EVENT_HANDLING_H__

#include "stdafx.h"
#include "Environment.h"

class GameSystem;

class GameEventHandling {
private:
	GameSystem* system = nullptr;

	GameEventHandling();

	Key moveUp = Key::KEY_W;
	Key moveDown = Key::KEY_S;
	Key moveLeft = Key::KEY_A;
	Key moveRight = Key::KEY_D;

public:
	static GameEventHandling* getInstance();

	void setGameSystem(GameSystem* system);

	void onKeyPressed(EventKeyboard::KeyCode c, Event* e);
	void onKeyReleased(EventKeyboard::KeyCode c, Event* e);

	void setKeyUp(EventKeyboard::KeyCode c);
	void setKeyDown(EventKeyboard::KeyCode c);
	void setKeyLeft(EventKeyboard::KeyCode c);
	void setKeyRight(EventKeyboard::KeyCode c);

	EventKeyboard::KeyCode getKeyUp();
	EventKeyboard::KeyCode getKeyDown();
	EventKeyboard::KeyCode getKeyLeft();
	EventKeyboard::KeyCode getKeyRight();
};


#endif // !__GAME_EVENT_HANDLING_H__
