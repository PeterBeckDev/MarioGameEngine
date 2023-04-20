#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H

#include "SDL.h"
#include <iostream>
#include "Commons.h"
#include <string>
#include "Texture2D.h"
#include "LevelMap.h"
#include <SDL_mixer.h>
#include "SoundManager.h"
using namespace std;

//class Texture2D;



class Character
{
protected:
	SDL_Renderer* m_renderer;
	SoundManager* m_sound;
	Texture2D* m_texture;
	Mix_Music* m_music;
	Mix_Chunk* m_sfx;
	
	bool m_moving_left;
	bool m_moving_right;

	bool m_can_jump;
	bool m_grounded;

	

	float m_collision_radius;

	bool m_alive = true;
public:
	FACING m_facing_direction;
	ANIMSTATE m_anim_state;
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;
	virtual void checkWrap();
	float contactForce;
		
	void PhysicsUpdate(float deltaTime, SDL_Event e);
	virtual void Jump();

	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, SoundManager* sound);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();

	float GetCollisionRadius();

	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_single_sprite_w, m_single_sprite_w); }

	bool IsJumping() { return !m_grounded; }
	void CancelJump() { if (m_velocity.y < 0) { m_velocity.y = 0; } }

	void SetAlive(bool alive) { m_alive = alive; }
	bool GetAlive() { return m_alive; }

	float m_movement_speed;
	float maxHzVel = MAXHZVEL;
	float leftAcc, rightAcc, HZcontactForce;

	bool walled;

	float m_single_sprite_w;
	float m_single_sprite_h;

private:
	LevelMap* m_current_level_map;

};

#endif // !_CHARACTER_H