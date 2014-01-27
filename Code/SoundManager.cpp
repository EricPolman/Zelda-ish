#include "SoundManager.h"


SoundManager::SoundManager(void)
{
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 1024 );
}


SoundManager::~SoundManager(void)
{
	instanceFlag = false;
	for(std::map<std::string, Mix_Chunk*>::iterator i = m_sounds.begin(); i != m_sounds.end(); ++i)
	{
		m_sounds.erase(i);
	}
}

bool SoundManager::instanceFlag = false;
SoundManager* SoundManager::single = NULL;
SoundManager* SoundManager::getInstance()
{
    if(! instanceFlag)
    {
        single = new SoundManager();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}


void SoundManager::Play(std::string a_soundName)
{
	Mix_PlayChannel( -1, m_sounds[a_soundName], 0 );
}


void SoundManager::SetMusic(std::string a_soundName, bool a_bStartPlaying)
{
	Mix_Music *m_pMusic = Mix_LoadMUS( std::string("assets/sounds/"+a_soundName+".wav").c_str() );
	
	if(a_bStartPlaying)
		Mix_PlayMusic( m_pMusic, -1 );
}


void SoundManager::Add(std::string a_soundName)
{
	m_sounds[a_soundName] = Mix_LoadWAV( std::string("assets/sounds/"+a_soundName+".wav").c_str() );
}

