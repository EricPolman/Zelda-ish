#pragma once
#include "includes.h"

class Tile
{
public:
	Tile(int a_iTileId, int a_iX, int a_iY);
	~Tile(void);

	static int TILE_WIDTH;
	static int TILE_HEIGHT;
	
	int m_iGridX;
	int m_iGridY;

	int m_iTileId;
};

