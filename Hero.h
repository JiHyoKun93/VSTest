#ifndef __HERO_H__
#define __HERO_H__

#include "stdafx.h"

#define MAX_HEROS 5

class Weapon {

};

class Amulet {

};

class Hero {
public:
	static Hero* getHeroByIndex(int i);
private:
	std::string firstname;
	std::string lastname;
	std::string description;

	Weapon weapon[6];
	Amulet amulet[20];

	SpriteFrame* frameImage;

	float maxHealth = 100;
	float recovery = 0;
	float armor = 0;
	float moveSpeed = 0;

	float might = 1;
	float speed = 1;
	float duration = 0;
	float area = 1;

	float cooldown = 1; // ¼öÄ¡°¡ ³·¾ÆÁú¼ö·Ï ´õ »¡¶óÁü
	float amount = 1;
	float revival = 0;
	float magnet = 0;

	float luck = 0;
	float growth = 0;
	float greed = 0;
	float curse = 0;

	float reroll = 0;
	float skip = 0;
	float banish = 0;

public:
	static void initHeros();

	inline const std::string& getFirstName() { return this->firstname; }
	inline const std::string& getLastName() { return this->lastname; }
	inline const std::string& getDescription() { return this->description; }

	inline SpriteFrame* getSpriteFrame() { return this->frameImage; }

	inline void setMaxHealth(float value) { this->maxHealth = value; }
	inline void setRecovery(float value) { this->recovery = value; }
	inline void setArmor(float value) { this->armor = value; }
	inline void setMoveSpeed(float value) { this->moveSpeed = value; }
	inline void setMight(float value) { this->might = value; }
	inline void setSpeed(float value) { this->speed = value; }
	inline void setDuration(float value) { this->duration = value; }
	inline void setArea(float value) { this->area = value; }
	inline void setCooldown(float value) { this->cooldown = value; }
	inline void setAmount(float value) { this->amount = value; }
	inline void setRevival(float value) { this->revival = value; }
	inline void setMagnet(float value) { this->magnet = value; }
	inline void setLuck(float value) { this->luck= value; }
	inline void setGrowth(float value) { this->growth = value; }
	inline void setGreed(float value) { this->greed = value; }
	inline void setCurse(float value) { this->curse = value; }
	inline void setReroll(float value) { this->reroll = value; }
	inline void setSkip(float value) { this->skip = value; }
	inline void setBanish(float value) { this->banish = value; }

	inline float getMaxHealth() {return this->maxHealth; }
	inline float getRecovery() { return this->recovery; }
	inline float getArmor() { return this->armor; }
	inline float getMoveSpeed() { return this->moveSpeed; }
	inline float getMight() {return this->might; }
	inline float getSpeed() {return this->speed; }
	inline float getDuration() { return this->duration; }
	inline float getArea() { return this->area; }
	inline float getCooldown() { return this->cooldown; }
	inline float getAmount() { return this->amount; }
	inline float getRevival() { return this->revival; }
	inline float getMagnet() { return this->magnet; }
	inline float getLuck() { return this->luck; }
	inline float getGrowth() { return this->growth; }
	inline float getGreed() {return this->greed; }
	inline float getCurse() {return this->curse; }
	inline float getReroll() { return this->reroll; }
	inline float getSkip() { return this->skip; }
	inline float getBanish() { return this->banish; }
};


#endif // !__HERO_H__
