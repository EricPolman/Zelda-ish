#pragma once
#include "includes.h"

class TileNode
{
public:
	TileNode(int a_iRow, int a_iCol, int a_iTileId);
	~TileNode(void);
	
	int m_iRow, m_iCol;
	int m_iTileId;

	CollisionRectangle m_collisionRectangle;

	void SetSurface(int a_iTileId);

	void Draw(Tmpl8::Surface* a_screen, Vector2 offset = Vector2(0,0));

private:
	void SetCollisionRectangle(CollisionType a_collisionType);
	Tmpl8::Surface* m_pTileSurface;
};
