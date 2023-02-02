#include "stdafx.h"
#include "GameEventHandling.h"
#include "GameSystem.h"
#include "SceneIngame.h"

static GameEventHandling* eventInstance;

GameEventHandling::GameEventHandling() {
	moveUp = (Key)UserDefault::getInstance()->getIntegerForKey("moveUp", (int)Key::KEY_W);
	moveDown = (Key)UserDefault::getInstance()->getIntegerForKey("moveDown", (int)Key::KEY_S);
	moveLeft = (Key)UserDefault::getInstance()->getIntegerForKey("moveLeft", (int)Key::KEY_A);
	moveRight = (Key)UserDefault::getInstance()->getIntegerForKey("moveRight", (int)Key::KEY_D);
}

GameEventHandling* GameEventHandling::getInstance() {
	return eventInstance == nullptr ? eventInstance = new GameEventHandling() : eventInstance;
}

void GameEventHandling::setGameSystem(GameSystem* system) {
	this->system = system;
}

void GameEventHandling::onKeyPressed(EventKeyboard::KeyCode c, Event* e) {

	if (c == moveUp) system->moveVector.y += 1;
	if (c == moveLeft) system->moveVector.x -= 1;
	if (c == moveDown) system->moveVector.y -= 1;
	if (c == moveRight) system->moveVector.x += 1;

	system->currentScene->inputMove(system->moveVector.getNormalized());

	if (system->isStatePlaying()) system->heroNode->setFacingDirection(system->moveVector);

	if (c == Key::KEY_ESCAPE) {
		if (system->isStatePlaying() || system->isStateTimeStop()) {
			system->setState(GameState::PAUSED);
			((SceneIngame*)system->currentScene)->showPauseDialog();
		}
		else if (system->getState() == GameState::PAUSED) {
			system->setState(GameState::PLAYING);
			((SceneIngame*)system->currentScene)->hidePauseDialog();
		}
	}
}

void GameEventHandling::onKeyReleased(EventKeyboard::KeyCode c, Event* e) {

	if (c == moveUp) system->moveVector.y -= 1;
	if (c == moveLeft) system->moveVector.x += 1;
	if (c == moveDown) system->moveVector.y += 1;
	if (c == moveRight) system->moveVector.x -= 1;

	system->currentScene->inputMove(system->moveVector.getNormalized());
}

void GameEventHandling::setKeyUp(EventKeyboard::KeyCode c) {
	this->moveUp = c;
	UserDefault::getInstance()->setIntegerForKey("moveUp", (int)c);
}

void GameEventHandling::setKeyDown(EventKeyboard::KeyCode c) {
	this->moveDown = c;
	UserDefault::getInstance()->setIntegerForKey("moveDown", (int)c);
}

void GameEventHandling::setKeyLeft(EventKeyboard::KeyCode c) {
	this->moveLeft = c;
	UserDefault::getInstance()->setIntegerForKey("moveLeft", (int)c);
}

void GameEventHandling::setKeyRight(EventKeyboard::KeyCode c) {
	this->moveRight = c;
	UserDefault::getInstance()->setIntegerForKey("moveRight", (int)c);
}

EventKeyboard::KeyCode GameEventHandling::getKeyUp() {
	return this->moveUp;
}

EventKeyboard::KeyCode GameEventHandling::getKeyDown() {
	return this->moveDown;
}

EventKeyboard::KeyCode GameEventHandling::getKeyLeft() {
	return this->moveLeft;
}

EventKeyboard::KeyCode GameEventHandling::getKeyRight() {
	return this->moveRight;
}
