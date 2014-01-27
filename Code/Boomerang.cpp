#include "Boomerang.h"


Boomerang::Boomerang(float a_fX, float a_fY, Vector2 a_direction, Entity* a_player)
	: Entity("", a_fX, a_fY)
{
	m_type = PLAYER_WEAPON;
	m_pSprite->LoadSpritesheet("boomerang", 10, 10, 4, 1);
	m_pSprite->AddAnimation("throwing", Vector2i(0,0), Vector2i(3,0));
	m_pSprite->PlayAnimation("throwing", true);
	m_pSprite->m_fAnimationSpeed = 3;
	m_collisionRect = CollisionRectangle(0,0, m_pSprite->GetWidth(), m_pSprite->GetHeight());
	m_bCollidesWithTiles = true;

	m_direction = a_direction;
	m_player = a_player;

	m_bReturnToSender = false;
	m_fDistanceTraveled = 0;
}


Boomerang::~Boomerang(void)
{
}


void Boomerang::Update(float a_fDeltaTime)
{
	Entity::Update(a_fDeltaTime);
	m_position = m_position + m_velocity;
	
	if(!m_bReturnToSender)
	{
		m_velocity = m_direction * a_fDeltaTime * 150;
		m_fDistanceTraveled += Vector2(m_direction * a_fDeltaTime * 150).Magnitude();
		if(m_fDistanceTraveled > 100)
		{
			m_bReturnToSender = true;
			m_bCollidesWithTiles = false;
		}
	}
	else
	{
		Vector2 player(m_player->GetPosition() + Vector2(
			m_player->m_collisionRect.x + m_player->m_collisionRect.width * 0.5f, 
			m_player->m_collisionRect.y + m_player->m_collisionRect.height * 0.5f)
		);
		m_velocity = m_direction * a_fDeltaTime * 150;
		m_direction = player - m_position;
		m_direction.Normalize();

		if(m_position.Distance(player) < 2)
		{
			m_state = REMOVED;
		}
	}
}

void Boomerang::HitWall()
{
	m_bReturnToSender = true;
	m_bCollidesWithTiles = false;
}


void Boomerang::Hit(Entity* a_pOther, CollisionInfo a_info)
{
	if(a_pOther->m_type == ENEMY || a_pOther->m_type == BOSS || a_pOther->m_type == DESTROYABLE)
	{
		m_bReturnToSender = true;
		m_bCollidesWithTiles = false;
	}
}