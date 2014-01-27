#include "SwordSlash.h"


SwordSlash::SwordSlash(Direction a_direction, float a_fX, float a_fY)
	: Entity("blank", a_fX, a_fY)
{
	m_type = SWORD_SLASH;
	m_pSprite->LoadSpritesheet("blank", 4, 4, 1, 1);
	switch(a_direction)
	{
	case DOWN:
		m_collisionRect.x = 17;
		m_collisionRect.y = 32;
		m_collisionRect.width = 8;
		m_collisionRect.height = 11;
		break;
	case RIGHT:
		m_collisionRect.x = 32;
		m_collisionRect.y = 17;
		m_collisionRect.width = 11;
		m_collisionRect.height = 8;
		break;
	case UP:
		m_collisionRect.x = 17;
		m_collisionRect.y = 5;
		m_collisionRect.width = 8;
		m_collisionRect.height = 11;
		break;
	case LEFT:
		m_collisionRect.x = 5;
		m_collisionRect.y = 17;
		m_collisionRect.width = 11;
		m_collisionRect.height = 8;
		break;
	}
}


SwordSlash::~SwordSlash(void)
{
}


void SwordSlash::Hit(Entity* a_pOther, CollisionInfo a_info)
{
	if(a_pOther->m_type == DESTROYABLE)
	{
		a_pOther->Hit(this, a_info);
	}
}
