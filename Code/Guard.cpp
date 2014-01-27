#include "Guard.h"


Guard::Guard(float a_fX, float a_fY, Direction a_direction, Room* a_room)
	: Entity("blank", a_fX, a_fY, a_room)
{
	m_pSprite->LoadSpritesheet("guard", 25, 30, 4, 1);
	m_pSprite->AddAnimation("0_idle", Vector2i(0,0), Vector2i(0,0));
	m_pSprite->AddAnimation("1_idle", Vector2i(1,0), Vector2i(1,0));
	m_pSprite->AddAnimation("2_idle", Vector2i(2,0), Vector2i(2,0));
	m_pSprite->AddAnimation("3_idle", Vector2i(3,0), Vector2i(3,0));
	
	m_direction = a_direction;

	switch(a_direction)
	{
	case DOWN:
		m_pSprite->PlayAnimation("0_idle", true);
		break;
	case RIGHT:
		m_pSprite->PlayAnimation("1_idle", true);
		break;
	case UP:
		m_pSprite->PlayAnimation("2_idle", true);
		break;
	case LEFT:
		m_pSprite->PlayAnimation("3_idle", true);
		break;
	}

	m_collisionRect = CollisionRectangle(-5,-5, m_pSprite->GetWidth() + 5, m_pSprite->GetHeight() + 5);
	m_bCollidesWithTiles = false;
}


Guard::~Guard(void)
{
}
