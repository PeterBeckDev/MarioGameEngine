#pragma once
#ifndef _GAMESCREENMANAGER_H
#define _GAMESCREENMANAGER_H

#include "Commons.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include "SoundManager.h"

class GameScreen;

class GameScreenManager
{
private:
	SDL_Renderer* m_renderer;
	GameScreen* m_current_screen;
	SoundManager* m_sound;
public:
	GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen, SoundManager* sound);
	~GameScreenManager();

	void Render();
	void Update(float deltaTime, SDL_Event e);

	void ChangeScreen(SCREENS new_screen);
};

#endif
