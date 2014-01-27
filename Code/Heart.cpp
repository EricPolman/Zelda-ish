#include "Heart.h"
#include "Player.h"

Heart::Heart(float a_fX, float a_fY, Room* a_room)
	: Entity("heart_pickup", a_fX, a_fY, a_room)
{
	m_type = PICKUP;
	m_pSprite->LoadSpritesheet("heart_pickup", 12, 10, 1, 1);;
	m_collisionRect = CollisionRectangle(0,0, m_pSprite->GetWidth(), m_pSprite->GetHeight());
	m_bCollidesWithTiles = false;
	m_pSprite->m_fAnimationSpeed = 1;
}


Heart::~Heart(void)
{
}


void Heart::Hit(Entity* a_pOther, CollisionInfo a_info)
{
	if(a_pOther->m_type == PLAYER)
	{
		((Player*)a_pOther)->DecreaseHealth(-2);
		m_state = REMOVED;
	}
}