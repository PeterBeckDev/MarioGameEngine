#pragma once
#ifndef _KOOPACHARACTER_H
#define _KOOPACHARACTER_H

#include "Character.h"

class KoopaCharacter : public Character
{
protected:

public:
	KoopaCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed, SoundManager* sound);
	~KoopaCharacter();
	void TakeDamage();
	void Jump();
	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;

	bool GetInjured() { return m_injured; }
	void FallOff();

	void checkWrap() override;
private:
	
	bool m_fall = false;
	bool m_injured;
	float m_injured_time;
	void FlipRightWayUp();
};

#endif