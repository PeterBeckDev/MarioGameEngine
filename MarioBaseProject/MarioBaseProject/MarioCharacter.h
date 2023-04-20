#pragma once
#ifndef _MARIOCHARACTER_H
#define _MARIOCHARACTER_H

#include "Character.h"

class MarioCharacter : public Character
{
public:
	MarioCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, SoundManager* sound);
	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;
	int WalkFrame();
private:
	
	float m_anim_timer;
};

#endif