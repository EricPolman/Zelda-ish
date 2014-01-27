#pragma once
#include "includes.h"
#include "Room.h"
#include "TileSurface.h"
#include "TileNode.h"
#include "World.h"

class TileManager
{
public:
	~TileManager(void);
	static TileManager* getInstance(void);

	void LoadBaseSprite(char* a_sPath);
	void LoadExistingMap();
	void ProcessTileMap();
	void Update(float a_fDeltaTime);
	void Draw(Tmpl8::Surface* a_screen);
	void SetRoom(int a_iIndex);
	Room* GetRoom(int a_iIndex){return m_rooms[a_iIndex];}
	Room* GetCurrentRoom(){return m_pCurrentRoom;}
	TileSurface* GetTileSurface(int id);
	
	World* m_pWorld;
private:
	Tmpl8::Surface* surface;

	Room* m_rooms[MAP_WIDTH / ROOM_WIDTH * MAP_HEIGHT / ROOM_HEIGHT];
	Room* m_pCurrentRoom;

	static bool instanceFlag;
	static TileManager *single;
	TileManager(void);

	Tmpl8::Surface* m_pBaseSprite;
	std::vector<TileSurface*> m_pTileSurfaces;
	TileNode* m_pTiles[MAP_WIDTH / TILE_WIDTH * MAP_HEIGHT / TILE_HEIGHT];
	
	void LoadTileSurfaces(int a_tileWidth, int a_tileHeight, int a_width, int a_height, int a_amountOfTiles);
	void ComposeMap();
};

#define Tiles TileManager::getInstance()