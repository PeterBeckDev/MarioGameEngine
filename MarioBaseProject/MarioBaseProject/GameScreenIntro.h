#pragma once
#ifndef _GAMESCREENINTRO_H
#define	_GAMESCREENINTRO_H

#include "GameScreen.h"
#include "GameScreenManager.h"
#include "Commons.h"
#include "LevelMap.h"
#include "TextRenderer.h"


#include <vector>

class Texture2D;

class GameScreenIntro : GameScreen
{

public:
	GameScreenIntro(SDL_Renderer* renderer,GameScreenManager* gsm, SoundManager* sound);
	~GameScreenIntro();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	
private:
	Texture2D* m_background_texture;
	bool SetUpLevel();

	LevelMap* m_level_map;
	SoundManager* m_sound;

	TextRenderer* m_text;
};

#endif // !_GAMESCREENINTRO_H
