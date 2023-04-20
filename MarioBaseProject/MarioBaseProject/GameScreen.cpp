#include "GameScreen.h"
#include "GameScreenManager.h"
#include <SDL_image.h>
#include <iostream>

using namespace std;

GameScreen::GameScreen(SDL_Renderer* renderer, GameScreenManager* gsm, SoundManager* sound)
{
	m_renderer = renderer;
	m_sound = sound;
	m_gsm = gsm;
}
GameScreen::~GameScreen()
{
	m_renderer = nullptr;

}

void GameScreen::Render()
{

}
void GameScreen::Update(float deltaTime, SDL_Event e)
{

}