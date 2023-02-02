#include "stdafx.h"
#include "ItemManagementSystem.h"
#include "ItemWhipComponent.h"
#include "ItemBookComponent.h"
#include "ItemGarlicComponent.h"
#include "ItemLaurelComponent.h"
#include "ItemMagicWandComponent.h"

static ItemManageMentSystem* instance = nullptr;

ItemManageMentSystem* ItemManageMentSystem::getInstance(){
	return instance == nullptr ? instance = new ItemManageMentSystem() : instance;
}

ItemManageMentSystem::ItemManageMentSystem() {
	for (int i = 0; i < ITEM_CAPACITY; i++) {
		items[i] = new ItemInfo();
	}
	initInfo();
}

void ItemManageMentSystem::initInfo(){
	UnitNode* hero = GameSystem::getInstance()->getHeroNode();

	items[0]->id = 0;
	items[0]->name = "Whip";
	items[0]->description = "Whip Attacks your ass";
	items[0]->base_weight = 3;
	items[0]->level = 1;
	(items[0]->spriteFrame = SpriteFrame::create(CHARACTOR_SHEET_FILE_NAME, Rect(288, 176, 16, 32)))->retain();
	items[0]->itemGet = [=]() {
		items[0]->level++;
	};

	items[1]->id = 1;
	items[1]->name = "MagicWand";
	items[1]->description = "Magic Wand is magical";
	items[1]->base_weight = 4;
	(items[1]->spriteFrame = SpriteFrame::create(CHARACTOR_SHEET_FILE_NAME, Rect(336, 144, 16, 32)))->retain();
	items[1]->itemGet = [=]() {
		items[1]->level++;
	};

	items[2]->id = 2;
	items[2]->name = "Galric";
	items[2]->description = "Smell";
	items[2]->base_weight = 10;
	(items[2]->spriteFrame = SpriteFrame::create(CHARACTOR_SHEET_FILE_NAME, Rect(336, 224, 16, 16)))->retain();
	items[2]->itemGet = [=]() {
		items[2]->level++;
	};

	items[3]->id = 3;
	items[3]->name = "Book";
	items[3]->description = "Book";
	items[3]->base_weight = 5;
	(items[3]->spriteFrame = SpriteFrame::create(CHARACTOR_SHEET_FILE_NAME, Rect(288, 288, 16, 32)))->retain();
	items[3]->itemGet = [=]() {
		items[3]->level++;
	};

	items[4]->id = 4;
	items[4]->name = "Laurel";
	items[4]->description = "this is a legacy is protect your james";
	items[4]->base_weight = 20;
	(items[4]->spriteFrame = SpriteFrame::create(CHARACTOR_SHEET_FILE_NAME, Rect(288, 256, 16, 16)))->retain();
	items[4]->itemGet = [=]() {
		items[4]->level++;
	};

}

void ItemManageMentSystem::initHeroNode(UnitNode* hero){
	{ auto comp = ItemWhipComponent::create(); comp->id = 0; hero->addComponent(comp); }
	{ auto comp = ItemMagicWandComponent::create(); comp->id = 1; hero->addComponent(comp); }
	{ auto comp = ItemGarlicComponent::create(); comp->id = 2; hero->addComponent(comp); }
	{ auto comp = ItemBookComponent::create(); comp->id = 3; hero->addComponent(comp); }
	{ auto comp = ItemLaurelComponent::create(); comp->id = 4; hero->addComponent(comp); }

}

std::vector<int> ItemManageMentSystem::gacha(){
	// 최초에는 base_weight 를 기반으로 weight를 만들어 줍니다.
	std::vector<float> weights;

	for (int i = 0; i < 5; i++) {
		//items[i]->weight = RandomHelper::random_int<int>(0, items[i]->base_weight);
		weights.push_back(items[i]->base_weight);
	}

	return throwDiceSequence(weights, 3, false);
	// items[i].weight 수치를 기반으로 정렬을 해줍니다.
}

ItemInfo* ItemManageMentSystem::getItemInfo(int index){
	return items[index];
}
