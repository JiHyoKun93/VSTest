#include "stdafx.h"
#include "GameSound.h"

static SoundSystem* soundInstance = nullptr;

SoundSystem* SoundSystem::getInstance() {
	return soundInstance == nullptr ? soundInstance = new SoundSystem() : soundInstance;
}

SoundSystem::SoundSystem() {
	musicVolume = UserDefault::getInstance()->getFloatForKey("music", 1.0f);
	sfxVolume = UserDefault::getInstance()->getFloatForKey("sfx", 1.0f);
	musicOn = UserDefault::getInstance()->getBoolForKey("musicOn", true);
	sfxOn = UserDefault::getInstance()->getBoolForKey("sfxOn", true);
}

void SoundSystem::setMusicVolume(float value) {
	musicVolume = value;
	UserDefault::getInstance()->setFloatForKey("music", musicVolume);

	if (backgroundMusicId == -1) return;
	AudioEngine::setVolume(backgroundMusicId, value);
}

void SoundSystem::setSfxVolume(float value) {
	sfxVolume = value;
	UserDefault::getInstance()->setFloatForKey("music", sfxVolume);

}

void SoundSystem::setMusicOn(bool value) {
	musicOn = value;
	UserDefault::getInstance()->setBoolForKey("musicOn", sfxVolume);

	if (!value) stopBackgroundMusic();
}

void SoundSystem::setSfxOn(bool value) {
	sfxOn = value;
	UserDefault::getInstance()->setBoolForKey("sfxOn", sfxVolume);
}

float SoundSystem::getMosicVolume() {
	return musicVolume;
}

float SoundSystem::getSfxVolume() {
	return sfxVolume;
}

bool SoundSystem::isMusicOn() {
	return musicOn;
}

bool SoundSystem::isSfxOn() {
	return sfxOn;
}

void SoundSystem::playSfx(const char* filepath) {
	if (sfxOn) AudioEngine::play2d(filepath, false, sfxVolume);
}

void SoundSystem::playMusic(const char* filepath) {
	if (musicOn) {
		stopBackgroundMusic();
		backgroundMusicId = AudioEngine::play2d(filepath, true, musicVolume);
	}
}

void SoundSystem::stopBackgroundMusic() {
	if (backgroundMusicId == -1) return;

	AudioEngine::stop(backgroundMusicId);
	backgroundMusicId = -1;
}



