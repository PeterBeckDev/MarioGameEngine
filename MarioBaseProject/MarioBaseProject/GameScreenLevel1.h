#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define	_GAMESCREENLEVEL1_H

#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "MarioCharacter.h"
#include "LuigiCharacter.h"
#include "KoopaCharacter.h"
#include "LevelMap.h"
#include "PowBlock.h"
#include "TextRenderer.h"

#include <vector>

class Character;
class MarioCharacter;
class Texture2D;
class PowBlock;

class GameScreenLevel1 : GameScreen
{
	
public:
	GameScreenLevel1(SDL_Renderer* renderer, GameScreenManager* gsm, SoundManager* sound);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock();
	void NextWave();
private:
	Texture2D* m_background_texture;
	bool SetUpLevel();
	MarioCharacter* my_mario_character;
	LuigiCharacter* my_luigi_character;
	KoopaCharacter* koopa;
	SoundManager* m_sound;
	void SetLevelMap();
	LevelMap* m_level_map;

	PowBlock* m_pow_block;

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_ypos;
	void DoScreenShake();

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

	vector<KoopaCharacter*> m_enemies;

	TextRenderer* m_text;
	int score, oldScore;
	int waveCount;
};

#endif // !_GAMESCREENLEVEL1_H
