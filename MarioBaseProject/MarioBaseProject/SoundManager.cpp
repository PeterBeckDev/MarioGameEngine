#include "SoundManager.h"

SoundManager::SoundManager()
{
	m_music = nullptr;
	m_sfx = nullptr;

}
SoundManager::~SoundManager()
{
	Mix_FreeMusic(m_music);
	m_music = nullptr;
	Mix_FreeChunk(m_sfx);
	m_sfx = nullptr;
	

}

void SoundManager::Update(float deltaTime, SDL_Event e)
{
	/*if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_DOWN)
	{
		StartMusic("Music/Mario.mp3");
	}
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_UP)
	{
		StopMusic();
	}*/
}

void SoundManager::LoadMusic(std::string path)
{
	m_music = Mix_LoadMUS(path.c_str());
	if (m_music == nullptr)
	{
		std::cout << "Failed to load music. Error" << Mix_GetError() << std::endl;
	}
}
void SoundManager::LoadChunk(std::string path)
{
	m_sfx = Mix_LoadWAV(path.c_str());
	if (m_sfx == nullptr)
	{
		std::cout << "Failed to load effect. Error" << Mix_GetError() << std::endl;
	}
}


void SoundManager::StartMusic(std::string path)
{
	LoadMusic("Music/Mario.mp3");
	if (Mix_PlayingMusic() == 0)
	{
	Mix_PlayMusic(m_music, -1);
	}
}

void SoundManager::StopMusic() 
{
	if (Mix_PlayingMusic() == 1)
	{
		Mix_HaltMusic();
	}
}

void SoundManager::PlaySfx(std::string path)
{
	LoadChunk(path);
	Mix_PlayChannel(-1, m_sfx, 0);
}



//LoadMusic("Music/Mario.mp3");
//if (Mix_PlayingMusic() == 0)
//{
//	Mix_PlayMusic(g_music, -1);
//}
	