#include "Rupee.h"
#include "Player.h"

Rupee::Rupee(float a_fX, float a_fY, Room* a_room)
	: Entity("Rupee", a_fX, a_fY, a_room)
{
	m_type = PICKUP;
	m_pSprite->LoadSpritesheet("rupee_pickup", 8, 14, 3, 1);
	m_pSprite->AddAnimation("shine", Vector2i(0,0), Vector2i(2,0));
	m_pSprite->PlayAnimation("shine", true);
	m_collisionRect = CollisionRectangle(0,0, m_pSprite->GetWidth(), m_pSprite->GetHeight());
	m_bCollidesWithTiles = false;
	m_pSprite->m_fAnimationSpeed = 1;
}


Rupee::~Rupee(void)
{
}


void Rupee::Hit(Entity* a_pOther, CollisionInfo a_info)
{
	if(a_pOther->m_type == PLAYER)
	{
		((Player*)a_pOther)->AddRupees(5);
		m_state = REMOVED;
	}
}