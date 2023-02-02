#include "stdafx.h"
#include "GameData.h"

static GameData* dataInstance = nullptr;
GameData* GameData::getInstance() {
	return dataInstance == nullptr ? dataInstance = new GameData() : dataInstance;
}
#ifdef DATA_ENCODE
float GameData::encode(float value) {
	return value + 1.0f;
}

int GameData::encode(int value) {
	return value + 1;
}

double GameData::encode(double value) {
	return value + 1.0;
}

float GameData::decode(float value) {
	return value - 1.0f;
}

int GameData::decode(int value) {
	return value - 1;
}

double GameData::decode(double value) {
	return value - 1.0;
}

float GameData::getStageTime() {
	return decode(stageTime);
}

int GameData::getStagetKills() {
	return decode(stageKills);
}

double GameData::getStageGold() {
	return decode(stageGold);
}

double GameData::getStageExp(){
	return decode(stageExp);
}

int GameData::getStagePlayerLevel(){
	return decode(stagePlayerLevel);
}

void GameData::setStageTime(float value) {
	this->stageTime = encode(value);
}

void GameData::addStageTime(float value){
	setStageTime(getStageTime() + value);
}

void GameData::setStageKills(int value) {
	this->stageKills = encode(value);
}

void GameData::addStageKills(int value) {
	setStageKills(getStagetKills() + value);
}

void GameData::setStageGold(double value) {
	this->stageGold = encode(value);
}

void GameData::setStageExp(double value){
	stageExp = encode(value);
}

void GameData::addStageExp(double value){
	setStageExp(getStageExp() + value);
}

void GameData::setStagePlayerLevel(int value){
	stagePlayerLevel = encode(value);
}

float GameData::getGold() {
	return decode(gold);
}

void GameData::setGold(double value) {
	this->gold = encode(value);
}

#else

float GameData::encode(float value) {
	return value;
}

int GameData::encode(int value) {
	return value;
}

double GameData::encode(double value) {
	return value;
}

float GameData::decode(float value) {
	return value;
}

int GameData::decode(int value) {
	return value;
}

double GameData::decode(double value) {
	return value;
}

float GameData::getStageTime() {
	return decode(stageTime);
}

int GameData::getStagetKills() {
	return decode(stageKills);
}

double GameData::getStageGold() {
	return decode(stageGold);
}

void GameData::setStageTime(float value) {
	this->stageTime = encode(value);
}

void GameData::setStageKills(int value) {
	this->stageKills = encode(value);
}

void GameData::addStageKills(int value) {
	setStageKills(getStagetKills() + value);
}

void GameData::setStageGold(double value) {
	this->stageGold = encode(value);
}

float GameData::getGold() {
	return decode(gold);
}

void GameData::setGold(double value) {
	this->gold = encode(value);
}

#endif
