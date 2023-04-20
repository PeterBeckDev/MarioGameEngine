#pragma once
#ifndef _GAMESCREENLEVEL2_H
#define	_GAMESCREENLEVEL2_H

#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "MarioCharacter.h"
#include "KoopaCharacter.h"
#include "LevelMap.h"
#include "TextRenderer.h"

#include <vector>

class Character;
class MarioCharacter;
class Texture2D;

class GameScreenLevel2 : GameScreen
{

public:
	GameScreenLevel2(SDL_Renderer* renderer, GameScreenManager* gsm, SoundManager* sound);
	~GameScreenLevel2();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePOWBlock();
	void NextWave();
private:
	Texture2D* m_background_texture;
	bool SetUpLevel();
	MarioCharacter* my_mario_character;
	KoopaCharacter* koopa;
	SoundManager* m_sound;
	void SetLevelMap();
	LevelMap* m_level_map;

	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);

	vector<KoopaCharacter*> m_enemies;

	TextRenderer* m_text;
	int score, oldScore;
	int waveCount;
};

#endif // !_GAMESCREENLEVEL1_2