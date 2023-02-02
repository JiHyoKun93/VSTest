#ifndef __GAME_SOUND_H__
#define __GAME_SOUND_H__

#include "stdafx.h"

class SoundSystem {
private:
	float musicVolume;
	float sfxVolume;

	bool sfxOn;
	bool musicOn;

	SoundSystem();

	int backgroundMusicId = -1;
public:
	static SoundSystem* getInstance();

	void setMusicVolume(float value);
	void setSfxVolume(float value);
	void setMusicOn(bool value);
	void setSfxOn(bool value);

	float getMosicVolume();
	float getSfxVolume();
	bool isMusicOn();
	bool isSfxOn();

	void playSfx(const char* filepath);
	void playMusic(const char* filepath);
	void stopBackgroundMusic();
};


#endif
