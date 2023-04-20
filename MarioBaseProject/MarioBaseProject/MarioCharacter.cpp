#include "MarioCharacter.h"
#include "constants.h"
#include "Character.h"

MarioCharacter::MarioCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, SoundManager* sound) : Character(renderer, imagePath, start_position, map, sound)
{
	m_movement_speed = MVMTSPEED;
	m_single_sprite_h = m_texture->GetHeight();
}


void MarioCharacter::Render()
{
	int leftOffset = 0.0f;
	m_single_sprite_w = 32;
	//animations
	if (m_anim_state == WALKING)
	{
		m_single_sprite_w = 28;
		leftOffset = WalkFrame();
	}
	

	SDL_Rect portion_of_sprite = { leftOffset, 0, m_single_sprite_w, m_single_sprite_h };
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
}

int MarioCharacter::WalkFrame()
{
	if (m_anim_timer < 1)
	{
		return MARIORUN1;
	}
	else if (m_anim_timer < 2)
	{
		return MARIORUN3;
	}	
	else if (m_anim_timer < 3)
	{
		return MARIORUN1;
	}	
	else if (m_anim_timer < 4)
	{
		return MARIORUN3;
	}
	else 
	{
		m_anim_timer = 0.0f;
		return MARIORUN1;
	}
}

void MarioCharacter::Update(float deltaTime, SDL_Event e)
{
	m_anim_timer += deltaTime * 20;
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			Jump();
			break;
		case SDLK_s:
			break;
		case SDLK_a:
			m_moving_left = true;
			break;
		case SDLK_d:
			m_moving_right = true;
			break;
		}
		break;
	case SDL_KEYUP:
		switch (e.key.keysym.sym)
		{
		case SDLK_w:
			break;
		case SDLK_s:
			break;
		case SDLK_a:
			m_moving_left = false;
			break;
		case SDLK_d:
			m_moving_right = false;
			break;
		}
		break;
	}

	

	Character::Update(deltaTime, e);
}