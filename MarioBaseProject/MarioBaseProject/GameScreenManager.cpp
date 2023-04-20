#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"
#include "GameScreenIntro.h"



GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen, SoundManager* sound)
{
	m_renderer = renderer;
	m_current_screen = nullptr;
	m_sound = sound;
	ChangeScreen(startScreen);
}
GameScreenManager::~GameScreenManager()
{
	m_renderer = nullptr;
	delete m_current_screen;
	m_current_screen = nullptr;
}

void GameScreenManager::Render()
{
	m_current_screen->Render();
}
void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	m_current_screen->Update(deltaTime,e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	//clear up the old screen
	if (m_current_screen != nullptr)
	{
		delete m_current_screen;
	}
	GameScreenLevel1* tempScreen1;
	GameScreenLevel2* tempScreen2;
	GameScreenIntro* tempScreenIntro;
	switch (new_screen)
	{
	case SCREEN_LEVEL1:
		tempScreen1 = new GameScreenLevel1(m_renderer, this, m_sound);
		m_current_screen = (GameScreen*)tempScreen1;
		tempScreen1 = nullptr;
		break;
	case SCREEN_LEVEL2:
		tempScreen2 = new GameScreenLevel2(m_renderer, this, m_sound);
		m_current_screen = (GameScreen*)tempScreen2;
		tempScreen2 = nullptr;
		break;
	case SCREEN_INTRO:
		tempScreenIntro = new GameScreenIntro(m_renderer,this, m_sound);
		m_current_screen = (GameScreen*)tempScreenIntro;
		tempScreenIntro = nullptr;
		break;
	default:
		;
	}
}