#pragma once
#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>
#include <string>
#include "Commons.h"
#include <SDL_mixer.h>
#include "GameScreenManager.h"


class GameScreen
{
protected:
	SDL_Renderer* m_renderer;
	GameScreenManager* m_gsm;
	SoundManager* m_sound;
public:
	GameScreen(SDL_Renderer* renderer, GameScreenManager* gsm, SoundManager* sound);
	~GameScreen();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
};

#endif // !_GAMESCREEN_H