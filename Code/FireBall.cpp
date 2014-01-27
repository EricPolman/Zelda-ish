#include "FireBall.h"
#include "Player.h"

FireBall::FireBall(Vector2 a_shootDirection, float a_fX, float a_fY, Room* a_room)
	: Entity("fireball", a_fX, a_fY, a_room)
{
	m_type = BOSS;
	m_pSprite->LoadSpritesheet("fireball", 16, 16, 1, 1);
	m_collisionRect = CollisionRectangle(4,4, 8, 8);
	m_bCollidesWithTiles = true;

	m_shootDirection = a_shootDirection + Vector2(24,24) - m_position;
	m_shootDirection.Normalize();
}


FireBall::~FireBall(void)
{
}


void FireBall::Hit(Entity* a_pOther, CollisionInfo a_info)
{
	if(a_pOther->m_type == PLAYER)
	{
		((Player*)a_pOther)->DecreaseHealth(1);
		m_state = REMOVED;
	}
}

void FireBall::Update(float a_fDeltaTime)
{
	Entity::Update(a_fDeltaTime);
	m_position = m_position + m_shootDirection * a_fDeltaTime * 180;

	if( m_position.x < -20 || m_position.y < -20 || 
		m_position.y > ROOM_HEIGHT + 20 || m_position.x > ROOM_WIDTH + 20)
	{
		m_state = REMOVED;
	}
}