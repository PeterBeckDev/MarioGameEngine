#include "KoopaCharacter.h"
#include "constants.h"
#include "Character.h"


KoopaCharacter::KoopaCharacter(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, FACING start_facing, float movement_speed, SoundManager* sound) : Character(renderer, imagePath, start_position, map, sound)
{
	m_facing_direction = start_facing;
	m_position = start_position;
	m_injured = false;

	m_single_sprite_w = 32;
	m_single_sprite_h = 30;

	maxHzVel = MAXHZVEL * 0.5f;
}
KoopaCharacter::~KoopaCharacter()
{

}
void KoopaCharacter::TakeDamage()
{
	m_injured = true;
	m_injured_time = INJURED_TIME;
	Jump();
}
void KoopaCharacter::Jump()
{
	m_velocity.y = -100;

}
void KoopaCharacter::Render()
{
	//variable to hold the left position of the sprite we want to draw;
	int left = 0.0f;

	//if injured move the left position to be the left position of the second image of the sprite sheet;
	if (m_injured)
		left = m_single_sprite_w;
	//get the portion of the sprite sheet you want to draw
	SDL_Rect portion_of_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h };

	//determine where you want it drawn
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	//then ndraw it facing the correct direction
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}
}
void KoopaCharacter::Update(float deltaTime, SDL_Event e)
{
	

	if (!m_injured)
	{
		if(m_facing_direction == FACING_LEFT)
		{
			m_moving_left = true;
			m_moving_right = false;

		}
		else if (m_facing_direction == FACING_RIGHT)
		{
			m_moving_left = false;
			m_moving_right = true;
		}
	}
	else
	{
		m_moving_right = false;
		m_moving_left = false;

		m_injured_time -= deltaTime;

		if (m_injured_time <= 0.0f)
			FlipRightWayUp();
	}

	if (m_fall)
	{
		m_position.y += 1000 * deltaTime;
	}
	else {
		Character::Update(deltaTime, e);

		
	}

	

}

void KoopaCharacter::checkWrap()
{
	if (m_position.x < 5)
	{
		m_position.x = MAP_WIDTH * TILE_WIDTH - 5;
	}
	else if (m_position.x > MAP_WIDTH * TILE_WIDTH - 5)
	{
		m_position.x = 5;
	}
	if (m_position.y > MAP_HEIGHT * TILE_HEIGHT - 4 * TILE_HEIGHT)
	{
		if (m_position.x < 5 || (m_position.x > MAP_WIDTH * TILE_WIDTH - 5))
		{
			m_position.y = TILE_HEIGHT;
		}
	}
}

void KoopaCharacter::FlipRightWayUp()
{
	if (m_facing_direction == FACING_LEFT)
	{
		m_facing_direction = FACING_RIGHT;
	}
	else
	{
		m_facing_direction = FACING_LEFT;
	}
	m_injured = false;
	Jump();
}

void KoopaCharacter::FallOff()
{
	m_fall = true;
}