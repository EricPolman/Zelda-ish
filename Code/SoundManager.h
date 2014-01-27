#pragma once
#include "includes.h"

class SoundManager
{
public:
	~SoundManager(void);
	static SoundManager* getInstance(void);
	std::map<std::string, Mix_Chunk*> m_sounds;
	void Play(std::string soundName);
	void Add(std::string soundName);
	void SetMusic(std::string soundName, bool a_bStartPlaying);
private:
	static bool instanceFlag;
	static SoundManager *single;
	SoundManager(void);

	Mix_Music* m_pMusic;
};

#define Sounds SoundManager::getInstance()