#include "Aganihm.h"
#include "Lightning.h"
#include "FireBall.h"
#include "Player.h"


Aganihm::Aganihm(float a_fX, float a_fY, Room* a_room)
	: Entity("blank", a_fX, a_fY, a_room)
{
	m_type = BOSS;
	m_bossState = BOSS_IDLE;
	m_pSprite->LoadSpritesheet("aganihm", 64, 64, 10, 5);
	m_collisionRect = CollisionRectangle(16, 12, 32, 34);
	m_bCollidesWithTiles = false;
	
	m_pSprite->AddAnimation("0_idle", Vector2i(0,0), Vector2i(0,0));
	m_pSprite->AddAnimation("1_idle", Vector2i(0,1), Vector2i(0,1));
	m_pSprite->AddAnimation("2_idle", Vector2i(0,2), Vector2i(0,2));
	m_pSprite->AddAnimation("3_idle", Vector2i(0,3), Vector2i(0,3));

	m_pSprite->AddAnimation("0_stunned", Vector2i(1,0), Vector2i(1,0));
	m_pSprite->AddAnimation("1_stunned", Vector2i(1,1), Vector2i(1,1));
	m_pSprite->AddAnimation("2_stunned", Vector2i(1,2), Vector2i(1,2));
	m_pSprite->AddAnimation("3_stunned", Vector2i(1,3), Vector2i(1,3));
	
	m_pSprite->AddAnimation("0_attack", Vector2i(2,0), Vector2i(9,0));
	m_pSprite->AddAnimation("1_attack", Vector2i(2,1), Vector2i(6,1));
	m_pSprite->AddAnimation("2_attack", Vector2i(2,2), Vector2i(6,2));
	m_pSprite->AddAnimation("3_attack", Vector2i(2,3), Vector2i(6,3));
	
	m_pSprite->AddAnimation("die", Vector2i(0,4), Vector2i(5,4));
	m_pSprite->AddAnimation("teleport", Vector2i(8,4), Vector2i(9,4));

	m_pSprite->PlayAnimation("0_idle", true);
	m_pSprite->m_fAnimationSpeed = 1;

	m_direction = DOWN;
	m_fStunTimer = 0;
	m_iHealth = 10;
	
	m_fInvulnerabilityTimer = 0;
	m_fStunTimer = 0;
	INVULNERABLE_TIME = 0.3f;
	m_bInvulnerable = false;
	m_bAttackFired = false;

	m_bCanAttack = false;
	m_fAttackTimer = 0;
	
	m_bCanTeleport = false;
	m_fTeleportTimer = 0;
	
	m_teleportPositions[0] = Vector2(206,200);
	m_teleportPositions[1] = Vector2(269,121);
	m_teleportPositions[2] = Vector2(211,274);
	m_teleportPositions[3] = Vector2(194,424);
	m_teleportPositions[4] = Vector2(77,242);
	m_teleportPositions[5] = Vector2(386,242);
}


Aganihm::~Aganihm(void)
{
}


std::ostringstream dirStream;
void Aganihm::Update(float a_fDeltaTime)
{
	Entity::Update(a_fDeltaTime);

	Vector2 direction = m_pPlayer->GetPosition() + Vector2(24,24) - (m_position + Vector2(32,32));
	direction.Normalize();

	if(!m_bCanTeleport)
	{
		m_fTeleportTimer += a_fDeltaTime;
		if(m_fTeleportTimer > 8)
		{
			m_fTeleportTimer = 0;
			m_bCanTeleport = true;
		}
	}

	switch(m_bossState)
	{
	case BOSS_IDLE:

		if(m_bCanTeleport)
		{
			m_bossState = BOSS_TELEPORTING;
			m_bCanTeleport = false;
			m_pSprite->PlayAnimation("teleport", false);
		}
		

		if(!m_bCanAttack)
		{
			m_fAttackTimer += a_fDeltaTime;
			if(m_fAttackTimer > 1.3f)
			{
				m_fAttackTimer = 0;
				m_bCanAttack = true;
			}
		}

		if(abs(direction.y) > abs(direction.x))
		{
			if(direction.y < 0)
			{
				if(m_direction != UP)
				{
					m_direction = UP;
					m_pSprite->PlayAnimation("2_idle", true);
				}
			}
			else
			{
				if(m_direction != DOWN)
				{
					m_direction = DOWN;
					m_pSprite->PlayAnimation("0_idle", true);
				}
			}
		}
		else
		{
			if(direction.x > 0)
			{
				if(m_direction != RIGHT)
				{
					m_direction = RIGHT;
					m_pSprite->PlayAnimation("1_idle", true);
				}
			}
			else
			{
				if(m_direction != LEFT)
				{
					m_direction = LEFT;
					m_pSprite->PlayAnimation("3_idle", true);
				}
			}
		}
		
		switch(m_direction)
		{
		case DOWN:
			if(m_bCanAttack)
				Zap();
			break;
		case UP:
		case LEFT:
		case RIGHT:
			if(m_bCanAttack)
				ShootBall();
			break;
		}
		break;
	case BOSS_TELEPORTING:
		if(m_pSprite->m_sCurrentAnimation != "teleport")
		{
			Vector2 newPos = m_teleportPositions[rand()%6];
			if(newPos.x == m_position.x && newPos.y == m_position.y)
			{
				newPos = m_teleportPositions[rand()%6];
			}
			m_position = newPos;
			dirStream << m_direction;
			m_pSprite->PlayAnimation(dirStream.str()+"_idle", true);
			m_bossState = BOSS_IDLE;
			dirStream.str("");
		}
		break;
	case BOSS_STUNNED:
		m_fStunTimer += a_fDeltaTime;
		if(m_fStunTimer > 2.8f)
		{
			m_fStunTimer = 0;
			m_bossState = BOSS_IDLE;
			dirStream << m_direction;
			m_pSprite->PlayAnimation(dirStream.str()+"_idle", true);
			dirStream.str("");
		}
		break;
	case BOSS_ATTACKING:
		if(!m_bAttackFired)
		{
			if(m_direction == DOWN)
			{
				if(m_pSprite->m_currentFrame.x == 9 && m_pSprite->m_currentFrame.y == 0 )
				{
					new Lightning(m_position.x + 32 - (415/5/2), m_position.y + 42);
					m_bAttackFired = true;
				}
			}
			else
			{
				if(m_pSprite->m_sCurrentAnimation == "idle")
				{
					switch(m_direction)
					{
					case LEFT:
						new FireBall(m_pPlayer->GetPosition(), m_position.x + 12, m_position.y + 15);
						break;
					case RIGHT:
						new FireBall(m_pPlayer->GetPosition(), m_position.x + 42, m_position.y + 15);
						break;
					case UP:
						new FireBall(m_pPlayer->GetPosition(), m_position.x + 24, m_position.y + 3);
						break;
					}
					m_bAttackFired = true;
				}
			}
		}
		if(m_pSprite->m_sCurrentAnimation == "idle")
		{
			dirStream << m_direction;
			m_pSprite->PlayAnimation(dirStream.str()+"_idle", true);
			m_bossState = BOSS_IDLE;
			dirStream.str("");
			m_bAttackFired = false;
		}
		break;
	case BOSS_HIT:
		if(m_iHealth < 1)
		{
			m_bossState = BOSS_DYING;
			m_pSprite->m_fAnimationSpeed = 1;
			m_pSprite->PlayAnimation("die", false);
		}
		else
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
					dirStream << m_direction;
					m_pSprite->PlayAnimation(dirStream.str()+"_idle", true);
					m_bossState = BOSS_IDLE;
					dirStream.str("");
				}
			}
		}
		break;
	case BOSS_DYING:
		if(m_pSprite->m_sCurrentAnimation == "idle")
		{
			m_state = REMOVED;
			m_bIsVisible = false;
		}
		break;

	}
}

void Aganihm::Hit(Entity* a_pOther, CollisionInfo a_info)
{
	
	switch(a_pOther->m_type)
	{
	case PLAYER_WEAPON:
		if(m_bossState != BOSS_DYING && m_bossState != BOSS_HIT &&  m_bossState != BOSS_TELEPORTING)
		{
			m_bossState = BOSS_STUNNED;
			dirStream << m_direction;
			m_pSprite->PlayAnimation(dirStream.str()+"_stunned", true);
			dirStream.str("");
		}
		break;
	case SWORD_SLASH:
		if(m_bossState == BOSS_STUNNED)
		{
			if(!m_bInvulnerable)
			{
				m_bossState = BOSS_HIT;
 				m_iHealth--;
				m_bInvulnerable = true;
			}
		}
		else if(m_bossState != BOSS_DYING && m_bossState != BOSS_HIT)
		{
			((Player*)m_pPlayer)->DecreaseHealth(1);
			((Player*)m_pPlayer)->KnockBack(m_position);
		}
		break;
		
	case PLAYER:
		if(m_bossState != BOSS_DYING && m_bossState != BOSS_HIT && m_bossState != BOSS_STUNNED)
		{
			((Player*)m_pPlayer)->DecreaseHealth(1);
			((Player*)m_pPlayer)->KnockBack(m_position);
		}
		break;
	default:
		break;
	}
}

void Aganihm::Zap()
{
	m_bossState = BOSS_ATTACKING;
	m_bAttackFired = false;
	m_bCanAttack = false;
	m_pSprite->PlayAnimation("0_attack", false);
}

void Aganihm::ShootBall()
{
	m_bossState = BOSS_ATTACKING;
	m_bAttackFired = false;
	m_bCanAttack = false;
	dirStream << m_direction;
	m_pSprite->PlayAnimation(dirStream.str()+"_attack", false);
	dirStream.str("");
}