#include "GameScreenIntro.h"
#include "GameScreenManager.h"
#include "Texture2D.h"
#include <iostream>

GameScreenIntro::GameScreenIntro(SDL_Renderer* renderer, GameScreenManager* gsm,SoundManager* sound) : GameScreen(renderer, gsm, sound)
{
	SetUpLevel();
	m_sound = sound;
	m_renderer = renderer;
	m_gsm = gsm;
}

void GameScreenIntro::Render()
{
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	m_text->Render(200, 300);
}
void GameScreenIntro::Update(float deltaTime, SDL_Event e)
{
	if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN)
	{
		m_gsm->ChangeScreen(SCREEN_LEVEL1);
	}
}
bool GameScreenIntro::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/Intro.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
	//text
	m_text = new TextRenderer(m_renderer);

	if (!m_text->LoadFont("Fonts/PressStart.ttf", 14, "HIT ENTER TO START", { 0xFF,0xFF,0xFF,0xFF }))
	{
		std::cout << "Failed to load text renderer! " << TTF_GetError << std::endl;
		return false;
	}
}
