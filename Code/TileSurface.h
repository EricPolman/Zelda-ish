#pragma once
#include "includes.h"

class TileSurface
{
public:
	TileSurface(int a_iTileId, Tmpl8::Surface* a_pTileSurface);
	~TileSurface(void);
	
	int m_iTileId;
	CollisionType m_collisionType;
	Tmpl8::Surface* m_pTileSurface;

	bool CompareSurfaces(Tmpl8::Surface* m_pOther); //Returns true if there is a difference.
};