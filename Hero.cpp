#include "stdafx.h"
#include "Hero.h"

static Hero* heros[MAX_HEROS] = {nullptr,};

Hero* Hero::getHeroByIndex(int i) {
	if (heros[0] == nullptr) initHeros();

	return heros[i];
}

void Hero::initHeros(){

	Hero* hero = new Hero();
	
	hero->firstname = "Antonio";
	hero->lastname = "Belpaese";
	hero->description = "Gains 10% more damage every 10 levels (max +50%)";
	hero->maxHealth = 120;
	hero->armor = 1;
	hero->frameImage = SpriteFrame::create("res/player-spritemap-v9.png", Rect(0, 0, 34, 34));
	hero->frameImage->getTexture()->setAliasTexParameters();
	hero->frameImage->retain();
	heros[0] = hero;

	hero = new Hero();
	hero->firstname = "Imelda";
	hero->lastname = "Belpaese";
	hero->description = "1Gains 10% more damage every 10 levels (max +50%)";
	hero->maxHealth = 100;
	hero->frameImage = SpriteFrame::create("res/player-spritemap-v9.png", Rect(0, 0, 34, 34));
	hero->frameImage->getTexture()->setAliasTexParameters();
	hero->frameImage->retain();
	heros[1] = hero;

	hero = new Hero();
	hero->firstname = "Pasqualina";
	hero->lastname = "Belpaese";
	hero->description = "2Gains 10% more damage every 10 levels (max +50%)";
	hero->maxHealth = 100;
	hero->speed = 1.1;
	hero->frameImage = SpriteFrame::create("res/player-spritemap-v9.png", Rect(0, 0, 34, 34));
	hero->frameImage->getTexture()->setAliasTexParameters();
	hero->frameImage->retain();
	heros[2] = hero;

	hero = new Hero();
	hero->firstname = "Gennaro";
	hero->lastname = "Belpaese";
	hero->description = "3Gains 10% more damage every 10 levels (max +50%)";
	hero->maxHealth = 120;
	hero->speed = 1.0;
	hero->amount = 1;
	hero->frameImage = SpriteFrame::create("res/player-spritemap-v9.png", Rect(0, 0, 34, 34));
	hero->frameImage->getTexture()->setAliasTexParameters();
	hero->frameImage->retain();
	heros[3] = hero;

	hero = new Hero();
	hero->firstname = "Arca";
	hero->lastname = "Ladonna";
	hero->description = "4Gains 10% more damage every 10 levels (max +50%)";
	hero->maxHealth = 120;
	hero->might = 1.1;
	hero->frameImage = SpriteFrame::create("res/player-spritemap-v9.png", Rect(0, 0, 34, 34));
	hero->frameImage->getTexture()->setAliasTexParameters();
	hero->frameImage->retain();
	heros[4] = hero;

}
