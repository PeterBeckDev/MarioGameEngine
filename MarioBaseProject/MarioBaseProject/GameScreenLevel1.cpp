#include "GameScreenLevel1.h"
#include "GameScreenManager.h"
#include "Texture2D.h"
#include "Character.h"
#include "MarioCharacter.h"
#include <iostream>
#include "Collisions.h"
#include "PowBlock.h"
#include <SDL_ttf.h>

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer,  GameScreenManager* gsm, SoundManager* sound) : GameScreen(renderer, gsm, sound)
{
	m_sound = sound;
	SetUpLevel();
	score = 0;
	oldScore = score;
	waveCount = 2;
}
GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete my_mario_character;
	my_mario_character = nullptr;
	delete my_luigi_character;
	my_luigi_character = nullptr;
	delete m_pow_block;
	m_pow_block = nullptr;
	m_enemies.clear();
}

void GameScreenLevel1::Render()
{
	// draw the enemies
		for (int i = 0; i < m_enemies.size(); i++)
		{
			m_enemies[i]->Render();
		}

	//draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
	//draw characters
	my_mario_character->Render();
	my_luigi_character->Render();
	m_pow_block->Render();
	m_background_texture->Render(Vector2D(0, m_background_ypos), SDL_FLIP_NONE);

	
	m_text->Render(200, 10);
	
	
}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	if (oldScore != score)
	{
		oldScore = score;
		m_text->LoadFont("Fonts/PressStart.ttf", 14, "SCORE: " + std::to_string(score), { 0xFF,0xFF,0xFF,0xFF });
	}
	
	UpdateEnemies(deltaTime, e);

	my_mario_character->Update(deltaTime, e);
	my_luigi_character->Update(deltaTime, e);
	my_mario_character->checkWrap();
	my_luigi_character->checkWrap();

	UpdatePOWBlock();
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_ypos = sin(m_wobble);
		m_background_ypos *= 3.0f;
		if (m_shake_time <= 0.0f)
		{
			m_screenshake = false;
			m_background_ypos = 0.0f;
		}
	}
	
}
bool GameScreenLevel1::SetUpLevel()
{
	SetLevelMap();

	CreateKoopa(Vector2D(150, 32), FACING_RIGHT, KOOPA_MVMT);
	CreateKoopa(Vector2D(325, 32), FACING_LEFT, KOOPA_MVMT);


	m_sound->StartMusic("Music/Mario.mp3");

	//set up player character
	my_mario_character = new MarioCharacter(m_renderer, "Images/MarioSprites.png", Vector2D(64, 320), m_level_map, m_sound);
	my_luigi_character = new LuigiCharacter(m_renderer, "Images/LuigiSprites.png", Vector2D(128, 320), m_level_map, m_sound);

	//set up pow
	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_ypos = 0.0f;

	//load texture
	m_background_texture = new Texture2D( m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
	//text renderer
	
	m_text = new TextRenderer(m_renderer);

	if (!m_text->LoadFont("Fonts/PressStart.ttf", 14, "SCORE: " + std::to_string(score), { 0xFF,0xFF,0xFF,0xFF }))
	{
		std::cout << "Failed to load text renderer! " << TTF_GetError << std::endl;
		return false;
	}
}

void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,2,2,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}

	//set the new one
	m_level_map = new LevelMap(map);
}

void  GameScreenLevel1::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(my_mario_character->GetCollisionBox(), m_pow_block->GetCollisionBox()) && m_pow_block->IsAvailable())
	{
		if (my_mario_character->IsJumping() && my_mario_character->m_velocity.y < 0)
		{
			DoScreenShake();
			m_pow_block->TakeHit();
			my_mario_character->CancelJump();
		}
	}
}

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
	if (!m_enemies.empty())
	{
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			m_enemies[i]->TakeDamage();
		}
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime,SDL_Event e)
{
	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			m_enemies[i]->Update(deltaTime, e);
			m_enemies[i]->checkWrap();
			//check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) && (m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Box(m_enemies[i]->GetCollisionBox(), my_mario_character->GetCollisionBox()))
				{
					if (m_enemies[i]->GetInjured())
					{
						
						m_enemies[i]->SetAlive(false);
						m_enemies[i]->FallOff();
					}
					else
					{
						if (my_mario_character->IsJumping() && my_mario_character->m_velocity.y > 0)
						{
							m_enemies[i]->TakeDamage();
							my_mario_character->Jump();
						}
						else
						{

						}
						
					}
				}

			}

			//remove dead enemies and off screen
			if (!m_enemies[i]->GetAlive() && m_enemies[i]->m_position.y > MAP_HEIGHT * TILE_HEIGHT)
			{
				score += 100;
				enemyIndexToDelete = i;
			}
			if (enemyIndexToDelete != -1)
			{
				m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
				enemyIndexToDelete = -1;
			}
		}
	}
	else NextWave();

	
}

void GameScreenLevel1::NextWave()
{
	waveCount++;
	for (int i = 1; i <= waveCount + 1; i++)
	{
		CreateKoopa(Vector2D(32 + (32*i), 32), FACING_RIGHT, KOOPA_MVMT);

	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	koopa = new KoopaCharacter(m_renderer, "Images/Koopa.png", position, m_level_map, direction, speed, m_sound);
	m_enemies.push_back(koopa);
}
