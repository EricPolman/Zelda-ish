#include "EnemyGoriya.h"


EnemyGoriya::EnemyGoriya(EnemyType a_type, Direction a_direction, float a_fX, float a_fY, Room* a_room)
	: Enemy(a_type, a_direction, a_fX, a_fY, a_room)
{	
	m_bDirectionChanged = false;
	m_pSprite->m_fAnimationSpeed = 2;
	if(a_type == RED_GORIYA)
		m_bInverseMovement = true;
	else
		m_bInverseMovement = false;
}


EnemyGoriya::~EnemyGoriya(void)
{
}


std::ostringstream directionStream;
void EnemyGoriya::Update(float a_fDeltaTime)
{
	Entity::Update(a_fDeltaTime);
	if(m_bInvulnerable)
	{
		m_fInvulnerabilityTimer += a_fDeltaTime;
		if((int)(m_fInvulnerabilityTimer * 10) % 2 == 0)
		{
			m_bIsVisible = false;
		}
		else
		{
			m_bIsVisible = true;
		}
			
		if(m_fInvulnerabilityTimer > INVULNERABLE_TIME)
		{
			m_fInvulnerabilityTimer = 0;
			m_bInvulnerable = false;
			m_bIsVisible = true;
		}
	}

	if(m_bInverseMovement)
	{
		switch(m_direction)
		{
		case UP:
			if(Input->IsKeyUp(SDLK_s) || Input->IsKeyUp(SDLK_DOWN))
				m_bDirectionChanged = false;
			break;
		case LEFT:
			if(Input->IsKeyUp(SDLK_d) || Input->IsKeyUp(SDLK_RIGHT))
				m_bDirectionChanged = false;
			break;
		case DOWN:
			if(Input->IsKeyUp(SDLK_w) || Input->IsKeyUp(SDLK_UP))
				m_bDirectionChanged = false;
			break;
		case RIGHT:
			if(Input->IsKeyUp(SDLK_a) || Input->IsKeyUp(SDLK_LEFT))
				m_bDirectionChanged = false;
			break;
		}
	}
	else
	{
		switch(m_direction)
		{
		case DOWN:
			if(Input->IsKeyUp(SDLK_s) || Input->IsKeyUp(SDLK_DOWN))
				m_bDirectionChanged = false;
			break;
		case RIGHT:
			if(Input->IsKeyUp(SDLK_d) || Input->IsKeyUp(SDLK_RIGHT))
				m_bDirectionChanged = false;
			break;
		case UP:
			if(Input->IsKeyUp(SDLK_w) || Input->IsKeyUp(SDLK_UP))
				m_bDirectionChanged = false;
			break;
		case LEFT:
			if(Input->IsKeyUp(SDLK_a) || Input->IsKeyUp(SDLK_LEFT))
				m_bDirectionChanged = false;
			break;
		}
	}
	m_position = m_position + m_velocity;
	m_velocity = Vector2();
	Vector2 moveDirection;
	
	if(m_enemyState != ENEMY_STUNNED)
	{
		if(Input->IsKeyDown(SDLK_w) || Input->IsKeyDown(SDLK_UP))
		{
			if(!m_bDirectionChanged && m_direction != UP)
			{
				if(m_bInverseMovement)
				{
					ChangeDirection(DOWN);
				}
				else
				{
					ChangeDirection(UP);
				}
			}
			moveDirection.y -= 1;
		}
		if(Input->IsKeyDown(SDLK_s) || Input->IsKeyDown(SDLK_DOWN))
		{
			if(!m_bDirectionChanged && m_direction != DOWN)
			{
				if(m_bInverseMovement)
				{
					ChangeDirection(UP);
				}
				else
				{
					ChangeDirection(DOWN);
				}
			}
			moveDirection.y += 1;
		}
		if(Input->IsKeyDown(SDLK_a) || Input->IsKeyDown(SDLK_LEFT))
		{
			if(!m_bDirectionChanged && m_direction != LEFT)
			{
				if(m_bInverseMovement)
				{
					ChangeDirection(RIGHT);
				}
				else
				{
					ChangeDirection(LEFT);	
				}
			}
			moveDirection.x -= 1;
		}
		if(Input->IsKeyDown(SDLK_d) || Input->IsKeyDown(SDLK_RIGHT))
		{
			if(!m_bDirectionChanged && m_direction != RIGHT)
			{
				if(m_bInverseMovement)
				{
					ChangeDirection(LEFT);					
				}
				else
				{
					ChangeDirection(RIGHT);
				}
			}
			moveDirection.x += 1;
		}

		if(moveDirection.x != 0 && moveDirection.y != 0)
		{
			moveDirection.Normalize();
		}
		else if(moveDirection.x == 0 && moveDirection.y == 0)
		{
			directionStream << m_direction;
			m_pSprite->PlayAnimation(directionStream.str()+"_walk", false);
			directionStream.str("");
			m_bDirectionChanged = false;
		}
		m_velocity = (m_bInverseMovement ?  moveDirection * -1: moveDirection) * a_fDeltaTime * 80;

	}
	else
	{
		m_fStunTimer += a_fDeltaTime;
		if(m_fStunTimer > 2.5f)
		{
			m_fStunTimer = 0;
			m_distanceTraveledInDirection = 0;
			m_bLookedAround = false;
			m_enemyState = ENEMY_ATTACKING;
		}
	}
}

void EnemyGoriya::ChangeDirection(Direction a_direction)
{
	m_direction = a_direction;
	directionStream << m_direction;
	m_pSprite->PlayAnimation(directionStream.str()+"_walk", true);
	directionStream.str("");
	m_bDirectionChanged = true;
}