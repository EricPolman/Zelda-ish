#include "GatePiece.h"


GatePiece::GatePiece(Direction a_side, float a_fX, float a_fY, Room* a_room)
	: Entity("blank", a_fX, a_fY, a_room)
{
	m_type = STATIC;
	if(a_side == LEFT)
	{
		m_pSprite->LoadSpritesheet("gate_left", 40, 40, 1, 1);
		m_collisionRect = CollisionRectangle(0,0, 16, m_pSprite->GetHeight());
	}
	else
	{
		m_pSprite->LoadSpritesheet("gate_right", 40, 40, 1, 1);
		m_collisionRect = CollisionRectangle(24,0, 16, m_pSprite->GetHeight());
	}
	m_bCollidesWithTiles = false;

}


GatePiece::~GatePiece(void)
{
}
