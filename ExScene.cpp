#include "stdafx.h"
#include "ExScene.h"
#include "Environment.h"

ExScene* ExScene::create(){
	auto ret = new ExScene();
	if (ret && ret->init()) ret->autorelease();
	else CC_SAFE_DELETE(ret);
	return ret;
}

bool ExScene::init(){
	if (!Scene::init()) return false;

	auto keybd = EventListenerKeyboard::create();
	keybd->onKeyPressed = [=](EventKeyboard::KeyCode c, Event* e) {
		if (c == EventKeyboard::KeyCode::KEY_F5) {
			PositionComponent::loadDocument();
		}
	};
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(keybd, this);

	//schedule(CC_SCHEDULE_SELECTOR(ExScene::logicPositionData), 1.0f);

	return true;
}

Node* ExScene::getOrCreateNode(const char* name) {
	Node* n = getChildByName(name);
	if (n == nullptr) {
		n = Node::create();
		n->setName(name);
		addChild(n);
	}
	return n;
}

Node* ExScene::getOrCreateNodeInMap(const char* name){
	if (map == nullptr) {
		return nullptr;
	}
	Node* n = map->getChildByName(name);
	if (n == nullptr) {
		map->addChild(n = Node::create());
		n->setName(name);
	}
	return n;
}

void ExScene::setMap(TMXTiledMap* map){
	if (this->map != nullptr) {
		map->removeFromParent();
		map = nullptr;
	}

	this->map = map;
	addChild(map);
}

TMXTiledMap* ExScene::getMap(){
	return map;
}

void ExScene::logicPositionData(float dt){
	PositionComponent::loadDocument();
}
