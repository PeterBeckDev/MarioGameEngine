#pragma once
#ifndef _SOUNDMANAGER_H
#define _SOUNDMANAGER_H

#include "Commons.h"
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

class SoundManager
{
private:
	
public:
	SoundManager();
	~SoundManager();

	Mix_Music* m_music;
	Mix_Chunk* m_sfx;

	void Update(float deltaTime, SDL_Event e);

	void LoadMusic(std::string path);
	void LoadChunk(std::string path);

	void StartMusic(std::string path);
	void StopMusic();

	void PlaySfx(std::string path);
};
#endif

