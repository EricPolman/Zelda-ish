#include "Enemy.h"
#include "DeathCloud.h"

Player* Enemy::g_pPlayer;

Enemy::Enemy(EnemyType a_type, Direction a_direction, float a_fX, float a_fY, Room* a_room)
	: Entity("blank", a_fX, a_fY, a_room)
{
	m_type = ENEMY;
	m_enemyType = a_type;
	switch(m_enemyType)
	{
	case RED_GORIYA:
		m_pSprite->LoadSpritesheet("goriya_red", 22, 26, 8, 1);
		m_pSprite->AddAnimation("0_walk", Vector2i(4,0), Vector2i(5,0));
		m_pSprite->AddAnimation("1_walk", Vector2i(0,0), Vector2i(1,0));
		m_pSprite->AddAnimation("3_walk", Vector2i(2,0), Vector2i(3,0));
		m_pSprite->AddAnimation("2_walk", Vector2i(6,0), Vector2i(7,0));
		m_collisionRect = CollisionRectangle(0,12, 22, 14);
		m_iHealth = 3;
		break;
	case GREEN_GORIYA:
		m_pSprite->LoadSpritesheet("goriya_green", 22, 26, 8, 1);
		m_pSprite->AddAnimation("0_walk", Vector2i(4,0), Vector2i(5,0));
		m_pSprite->AddAnimation("1_walk", Vector2i(0,0), Vector2i(1,0));
		m_pSprite->AddAnimation("3_walk", Vector2i(2,0), Vector2i(3,0));
		m_pSprite->AddAnimation("2_walk", Vector2i(6,0), Vector2i(7,0));
		m_collisionRect = CollisionRectangle(0,12, 22, 14);
		m_iHealth = 2;
		break;
	default:
	case GREEN_SOLDIER:
		m_pSprite->LoadSpritesheet("enemy_one", 18, 28, 16, 1);
		m_pSprite->AddAnimation("0_walk", Vector2i(0,0), Vector2i(1,0));
		m_pSprite->AddAnimation("1_walk", Vector2i(4,0), Vector2i(5,0));
		m_pSprite->AddAnimation("2_walk", Vector2i(12,0), Vector2i(13,0));
		m_pSprite->AddAnimation("3_walk", Vector2i(8,0), Vector2i(9,0));

		m_pSprite->AddAnimation("0_look", Vector2i(2,0), Vector2i(3,0));
		m_pSprite->AddAnimation("1_look", Vector2i(6,0), Vector2i(7,0));
		m_pSprite->AddAnimation("2_look", Vector2i(14,0), Vector2i(15,0));
		m_pSprite->AddAnimation("3_look", Vector2i(10,0), Vector2i(11,0));
		m_collisionRect = CollisionRectangle(2,14, 14, 14);
		m_pSprite->m_fAnimationSpeed = 1.5f;
		m_iHealth = 2;
		break;
	}
	m_enemyState = EnemyState::ENEMY_WALKING;
	m_spriteWalkDirection = DOWN;
	ChangeDirection(a_direction);
	INVULNERABLE_TIME = 0.4f;
	m_fInvulnerabilityTimer = 0;
	m_distanceTraveledInDirection = 0;
	m_fStunTimer = 0;
	m_bInvulnerable = m_bLookedAround = false;
	
	//m_pSprite->PlayAnimation("0_walk", true);
	m_maxDistance = 200;
}


Enemy::~Enemy(void)
{
}


void Enemy::Update(float a_fDeltaTime)
{
	Vector2 direction = g_pPlayer->GetPosition() + Vector2(16,16) - m_position;
	m_position = m_position + m_velocity;
	m_velocity.y = 0;
	m_velocity.x = 0;
	
	if(m_state != DEAD)
	{
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

		switch(m_enemyState)
		{
		case ENEMY_STUNNED:
			m_fStunTimer += a_fDeltaTime;
			if(m_fStunTimer > 1.5f)
			{
				m_fStunTimer = 0;
				m_distanceTraveledInDirection = 0;
				m_bLookedAround = false;
				m_enemyState = ENEMY_ATTACKING;
			}
			break;
		case ENEMY_ATTACKING:
			if(abs(direction.y) > abs(direction.x))
			{
				if(direction.y < 0)
				{
					if(m_spriteWalkDirection != UP)
					{
						m_spriteWalkDirection = UP;
						m_pSprite->PlayAnimation("2_walk", true);
					}
				}
				else
				{
					if(m_spriteWalkDirection != DOWN)
					{
						m_spriteWalkDirection = DOWN;
						m_pSprite->PlayAnimation("0_walk", true);
					}
				}
			}
			else
			{
				if(direction.x > 0)
				{
					if(m_spriteWalkDirection != RIGHT)
					{
						m_spriteWalkDirection = RIGHT;
						m_pSprite->PlayAnimation("1_walk", true);
					}
				}
				else
				{
					if(m_spriteWalkDirection != LEFT)
					{
						m_spriteWalkDirection = LEFT;
						m_pSprite->PlayAnimation("3_walk", true);
					}
				}
			}

			direction.Normalize();
			m_velocity = direction * 50 * a_fDeltaTime;

			break;
		case ENEMY_WALKING:
			m_distanceTraveledInDirection += a_fDeltaTime * 30;

			switch(m_spriteWalkDirection)
			{
			case DOWN:
				m_velocity.y = 30 * a_fDeltaTime;
				m_velocity.x = 0;
				break;
			case RIGHT:
				m_velocity.x = 30 * a_fDeltaTime;
				m_velocity.y = 0;			
				break;
			case UP:
				m_velocity.y = -30 * a_fDeltaTime;
				m_velocity.x = 0;			
				break;
			case LEFT:
				m_velocity.x = -30 * a_fDeltaTime;
				m_velocity.y = 0;			
				break;
			}
			if(m_distanceTraveledInDirection > m_maxDistance)
			{
				m_distanceTraveledInDirection = 0;
				m_enemyState = ENEMY_LOOKING_AROUND;
				m_bLookedAround = false;
				m_velocity.y = 0;
				m_velocity.x = 0;
				m_pSprite->m_fAnimationSpeed = 0.5f;
			}
			if(m_position.Distance(g_pPlayer->GetPosition()) < 100)
			{
				m_distanceTraveledInDirection = 0;
				m_bLookedAround = false;
				m_enemyState = ENEMY_ATTACKING;
			}
			break;
		case ENEMY_IDLE:

			break;
		case ENEMY_LOOKING_AROUND:
			switch(m_spriteWalkDirection)
			{
			case DOWN:
				if(m_pSprite->m_sCurrentAnimation != "0_look")
				{
					if(!m_bLookedAround)
					{
						m_pSprite->PlayAnimation("0_look", false);
						m_bLookedAround = true;
					}
					else
					{
						ChangeDirection(UP);
						m_pSprite->m_fAnimationSpeed = 1.5f;
					}
				}
				break;
			case RIGHT:
				if(m_pSprite->m_sCurrentAnimation != "1_look")
				{
					if(!m_bLookedAround)
					{
						m_pSprite->PlayAnimation("1_look", false);
						m_bLookedAround = true;
					}
					else
					{
						ChangeDirection(LEFT);
						m_pSprite->m_fAnimationSpeed = 1.5f;
					}
				}
				break;
			case UP:
				if(m_pSprite->m_sCurrentAnimation != "2_look")
				{
					if(!m_bLookedAround)
					{
						m_pSprite->PlayAnimation("2_look", false);
						m_bLookedAround = true;
					}
					else
					{
						ChangeDirection(DOWN);
						m_pSprite->m_fAnimationSpeed = 1.5f;
					}
				}
				break;
			case LEFT:
				if(m_pSprite->m_sCurrentAnimation != "3_look")
				{
					if(!m_bLookedAround)
					{
						m_pSprite->PlayAnimation("3_look", false);
						m_bLookedAround = true;
					}
					else
					{
						ChangeDirection(RIGHT);
						m_pSprite->m_fAnimationSpeed = 1.5f;
					}
				}
				break;
			}
			if(m_position.Distance(g_pPlayer->GetPosition()) < 100)
			{
				m_distanceTraveledInDirection = 0;
				m_bLookedAround = false;
				m_enemyState = ENEMY_ATTACKING;
			}
			break;
		}
	}
	Entity::Update(a_fDeltaTime);
}


void Enemy::Hit(Entity* a_pOther, CollisionInfo a_info)
{
	if(a_pOther->m_type == SWORD_SLASH)
	{
		if(!m_bInvulnerable)
		{
			a_info.depth.Normalize();
			a_info.depth = a_info.depth * 16;
			
			m_velocity.x += a_info.depth.x;
			m_velocity.y += a_info.depth.y;

			m_iHealth--;
			if(m_iHealth < 1)
			{
				new DeathCloud(this, m_position.x - 3, m_position.y + 6);
				m_state = DEAD;
			}
			else
			{
				m_bInvulnerable = true;
			}
		}
	}
	else if(a_pOther->m_type == PLAYER_WEAPON)
	{
		a_info.depth.Normalize();
		a_info.depth = a_info.depth * 10;
		m_velocity.x += a_info.depth.x;
		m_velocity.y += a_info.depth.y;
	
		m_enemyState = ENEMY_STUNNED;
	}
	else if(a_pOther->m_type != PICKUP)
	{
		a_info.depth.Normalize();
		a_info.depth = a_info.depth * 1.2f;
			
		if(a_info.depth.x > 0 && m_velocity.x < 1 || a_info.depth.x < 0 && m_velocity.x > -1)
		{
			m_velocity.x += a_info.depth.x;
		}
		if(a_info.depth.y > 0 && m_velocity.y < 1 || a_info.depth.y < 0 && m_velocity.y > -1)
		{
			m_velocity.y += a_info.depth.y;
		}
	}
}


void Enemy::ChangeDirection(Direction a_direction)
{
	m_spriteWalkDirection = a_direction;
	m_enemyState = ENEMY_WALKING;
	m_distanceTraveledInDirection = 0;
	switch(m_spriteWalkDirection)
	{
	case DOWN:
		m_pSprite->PlayAnimation("0_walk", true);
		break;
	case RIGHT:
		m_pSprite->PlayAnimation("1_walk", true);		
		break;
	case UP:	
		m_pSprite->PlayAnimation("2_walk", true);
		break;
	case LEFT:
		m_pSprite->PlayAnimation("3_walk", true);
		break;
	}
}