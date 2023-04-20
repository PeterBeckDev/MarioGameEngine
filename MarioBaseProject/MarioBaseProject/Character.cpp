#include "Character.h"
#include "Texture2D.h"
#include "constants.h"


Character::Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, LevelMap* map, SoundManager* sound)
{
	m_renderer = renderer;
	m_sound = sound;
	m_position = start_position;
	m_texture = new Texture2D(m_renderer);
	m_facing_direction = FACING_RIGHT;
	m_collision_radius = 15.0f;
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture!" << std::endl;
	}
	m_current_level_map = map;

	
}
Character::~Character()
{
	m_renderer = nullptr;
}

float Character::GetCollisionRadius()
{
	return m_collision_radius;
}

void Character::Render() 
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE, 0.0f);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL, 0.0f);
	}
	
}
void Character::Update(float deltaTime, SDL_Event e)
{
	//calculate movements before checking collsions so x velocity can be reset before passed to physics update
#pragma region Calculate horizontal Movement
	if (m_moving_left)
	{
		m_anim_state = WALKING;
		m_facing_direction = FACING_LEFT;
		leftAcc = -ACC;
		if (m_velocity.x < -maxHzVel)
		{
			m_velocity.x = -maxHzVel;
		}
	}
	else if (m_moving_right)
	{
		m_anim_state = WALKING;
		m_facing_direction = FACING_RIGHT;
		leftAcc = ACC;
		if (m_velocity.x > maxHzVel)
		{
			m_velocity.x = maxHzVel;
		}
	}
	else
	{
		m_anim_state = IDLE;
		if (m_velocity.x != 0)
		{
			leftAcc = -m_velocity.x * 10;
			if (m_velocity.x * m_velocity.x < 0.4f)
			{
				leftAcc = 0;
				m_velocity.x = 0;
			}
		}
	}
#pragma endregion 
	//These are the points where tile values will be checked against the level array
#pragma region init variables
	int forwardX = (int)(m_position.x + 1) / TILE_WIDTH;
	int backwardX = (int)(m_position.x + m_single_sprite_w - 1) / TILE_WIDTH;

	int footPos = (int)(m_position.y + m_single_sprite_h) / TILE_HEIGHT;
	int headPos = (int)(m_position.y / TILE_HEIGHT);
	
	int sidePos;
#pragma endregion 

#pragma region Detect Floor
	if (m_current_level_map->GetTileAt(footPos, forwardX) != 0 || m_current_level_map->GetTileAt(footPos, backwardX) != 0)
	{
		m_grounded = true;
		if (m_velocity.y > 0 && !walled)
		{
			m_velocity.y = 0;
			contactForce = GRAV;
		}
	}
	else {
		m_grounded = false;
		contactForce = 0;
	}
#pragma endregion 

#pragma region Detect Ceiling
	
	if (m_current_level_map->GetTileAt(headPos, forwardX) == 1 || m_current_level_map->GetTileAt(headPos, backwardX) == 1)
	{
		if (m_velocity.y < 0)
		{
			m_velocity.y = 0;
		}
	}
#pragma endregion 

#pragma region Detect Side Collisions
	//detects sides
	forwardX = (int)(m_position.x - 1) / TILE_WIDTH;
	backwardX = (int)(m_position.x + m_single_sprite_w + 1) / TILE_WIDTH;

	walled = false;
	HZcontactForce = 0;
	int numChecks = 3;

	for (int i = numChecks; i > 0; i--)
	{
		sidePos = (int)(((m_position.y + 1 + ((m_single_sprite_h - 2) * i/numChecks)) / TILE_HEIGHT));
		if ((m_current_level_map->GetTileAt(sidePos, forwardX) == 1 && (m_velocity.x < 0)) ||
			(m_current_level_map->GetTileAt(sidePos, backwardX) == 1 && (m_velocity.x > 0)))
		{
			m_velocity.x = 0;
			HZcontactForce = -leftAcc;
			walled = true;
		}
	}
#pragma endregion 

	//check if on the edge of the screen
	
	
	
	PhysicsUpdate(deltaTime, e);
}

void Character::checkWrap()
{
	if (m_position.x < 5)
	{
		m_position.x = MAP_WIDTH * TILE_WIDTH - 5;
	}
	else if (m_position.x > MAP_WIDTH * TILE_WIDTH - 5)
	{
		m_position.x = 5;
	}
}

void Character::PhysicsUpdate(float deltaTime, SDL_Event e)
{
	m_acceleration.y = GRAV - contactForce;
	m_velocity.y += m_acceleration.y * deltaTime;
	m_position.y += m_velocity.y * deltaTime;

	m_acceleration.x = leftAcc + HZcontactForce;
	m_velocity.x += m_acceleration.x * deltaTime;
	m_position.x += m_velocity.x * deltaTime;
}

void Character::Jump()
{
	if (m_grounded)
	{
		m_velocity.y = -540;
		m_grounded = false;
		contactForce = 0;
		m_sound->PlaySfx("Music/JumpEffect.wav");
	}

	

}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}
Vector2D Character::GetPosition()
{
	return m_position;
}