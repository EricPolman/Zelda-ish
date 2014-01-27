#include "TileNode.h"
#include "TileManager.h"

TileNode::TileNode(int a_iRow, int a_iCol, int a_iTileId)
{
	m_iRow = a_iRow;
	m_iCol = a_iCol;
	m_iTileId = a_iTileId;
	SetCollisionRectangle(Tiles->GetTileSurface(m_iTileId)->m_collisionType);
}


TileNode::~TileNode(void)
{
}


void TileNode::SetSurface(int a_iTileId)
{
	m_pTileSurface = Tiles->GetTileSurface(a_iTileId)->m_pTileSurface;
}


void TileNode::Draw(Tmpl8::Surface* a_screen, Vector2 offset)
{
	m_pTileSurface->CopyTo
		(a_screen, TILE_WIDTH * m_iCol + offset.x, TILE_HEIGHT * m_iRow + offset.y);
}


void TileNode::SetCollisionRectangle(CollisionType a_collisionType)
{
	switch(a_collisionType)
	{
	case BOOMERANGABLE:
	case FULL:
		m_collisionRectangle.x = m_iCol * TILE_WIDTH;
		m_collisionRectangle.y = m_iRow * TILE_HEIGHT;
		m_collisionRectangle.width = TILE_WIDTH;
		m_collisionRectangle.height = TILE_HEIGHT;
		break;
	case HALF_LEFT:
		m_collisionRectangle.x = m_iCol * TILE_WIDTH;
		m_collisionRectangle.y = m_iRow * TILE_HEIGHT;
		m_collisionRectangle.width = TILE_WIDTH / 2;
		m_collisionRectangle.height = TILE_HEIGHT;
		break;
	case HALF_RIGHT:
		m_collisionRectangle.x = m_iCol * TILE_WIDTH + TILE_WIDTH / 2;
		m_collisionRectangle.y = m_iRow * TILE_HEIGHT;
		m_collisionRectangle.width = TILE_WIDTH / 2;
		m_collisionRectangle.height = TILE_HEIGHT;
		break;
	case HALF_TOP:
		m_collisionRectangle.x = m_iCol * TILE_WIDTH;
		m_collisionRectangle.y = m_iRow * TILE_HEIGHT;
		m_collisionRectangle.width = TILE_WIDTH;
		m_collisionRectangle.height = TILE_HEIGHT / 2;
		break;
	case HALF_BOTTOM:
		m_collisionRectangle.x = m_iCol * TILE_WIDTH;
		m_collisionRectangle.y = m_iRow * TILE_HEIGHT + TILE_HEIGHT / 2;
		m_collisionRectangle.width = TILE_WIDTH;
		m_collisionRectangle.height = TILE_HEIGHT / 2;
		break;
	default:
	case NONE:
		break;
	}
}