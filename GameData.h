#ifndef __GAME_DATA_H__
#define __GAME_DATA_H__

#include "stdafx.h"
#include "Environment.h"

class GameData {
private:
	GameData() {}

	float stageTime = 0;
	int stageKills = 0;
	double stageGold = 0;
	int stagePlayerLevel = 1;
	double stageExp = 0;

	double gold;
public:
	static GameData* getInstance();

	// 암호화
	float encode(float value);
	int encode(int value);
	double encode(double value);
	// 복호화
	float decode(float value);
	int decode(int value);
	double decode(double value);


	float getStageTime();
	int getStagetKills();
	double getStageGold();
	double getStageExp();
	int getStagePlayerLevel();

	void setStageTime(float value);
	void addStageTime(float value);
	void setStageKills(int value);
	void addStageKills(int value);

	void setStageGold(double value);
	void setStageExp(double value);
	void addStageExp(double value);
	void setStagePlayerLevel(int value);

	float getGold();
	void setGold(double value);
};

#endif
