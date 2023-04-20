#pragma once
#ifndef _LUIGICHARACTER_H
#define _LUIGICHARACTER_H

#include "Character.h"

class LuigiCharacter : public Character
{
public:
	LuigiCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, SoundManager* sound);
	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;
	int WalkFrame();
private:

	float m_anim_timer;
};

#endif