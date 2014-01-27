#include "Shrub.h"
#include "Rupee.h"
#include "Heart.h"

Shrub::Shrub(float a_fX, float a_fY, Room* a_room)
	: Entity("shrub", a_fX, a_fY, a_room)
{
	m_type = DESTROYABLE;
	m_pSprite->LoadSpritesheet("shrub", 16, 16, 1, 1);
	m_collisionRect = CollisionRectangle(0,0, m_pSprite->GetWidth(), m_pSprite->GetHeight());
	m_bCollidesWithTiles = false;
}


Shrub::~Shrub(void)
{
}


void Shrub::Hit(Entity* a_pOther, CollisionInfo a_info)
{
	if(a_pOther->m_type == SWORD_SLASH)
	{
		if(rand()%50 > 35)
		{
			new Rupee(m_position.x + 4, m_position.y + 1);
		}
		else
		{
			if(rand()%50 > 35)
			{
				new Heart(m_position.x + 4, m_position.y + 1);
			}
		}
		m_state = REMOVED;
	}
}