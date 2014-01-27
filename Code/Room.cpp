#include "Room.h"
#include "Shrub.h"
#include "EntityManager.h"

Room::Room(Vector2i a_index, int (&a_idMap)[MAP_WIDTH / TILE_WIDTH][MAP_HEIGHT / TILE_HEIGHT])
{
	m_index = a_index;
	for(int tileX = 0; tileX < ROOM_WIDTH / TILE_WIDTH; tileX++)
	{
		for(int tileY = 0; tileY < ROOM_HEIGHT / TILE_HEIGHT; tileY++)
		{
			int index = tileY + tileX * ROWS_OF_TILES;
			m_tiles[index] = new TileNode(tileX, tileY, a_idMap[tileY + m_index.x * ROWS_OF_TILES][tileX + m_index.y * COLS_OF_TILES]);
			m_tiles[index]->SetSurface(m_tiles[index]->m_iTileId);
			if(m_tiles[index]->m_iTileId == 259) //Shrub-tile
			{
				new Shrub(tileY * TILE_HEIGHT, tileX * TILE_WIDTH, this);
			}
		}
	}
}

Room::~Room(void)
{
}


void Room::Update(float a_fDeltaTime)
{

}


void Room::Draw(Tmpl8::Surface* a_pTarget, Vector2 offset)
{
	for(int tileX = 0; tileX < COLS_OF_TILES; tileX++)
	{
		for(int tileY = 0; tileY < ROWS_OF_TILES; tileY++)
		{
			m_tiles[tileY + tileX * ROWS_OF_TILES]->Draw(a_pTarget, offset);
		}
	}
}