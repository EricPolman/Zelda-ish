#pragma once
#include "includes.h"
#include "TileNode.h"

class Room
{
public:
	Room(Vector2i a_index, int (&a_idMap)[MAP_WIDTH / TILE_WIDTH][MAP_HEIGHT / TILE_HEIGHT]);
	~Room(void);

	Vector2i m_index;

	void Update(float a_fDeltaTime);
	void Draw(Tmpl8::Surface* a_pTarget, Vector2 offset = Vector2(0,0));

	TileNode* m_tiles[ROOM_WIDTH / TILE_WIDTH * ROOM_HEIGHT / TILE_HEIGHT];
};

