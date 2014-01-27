#include "DarkForest.h"
#include "TileManager.h"

DarkForest::DarkForest(void)
	: Entity("blank", 0, 0, Tiles->GetRoom(15))
{
	m_pSprite->LoadSpritesheet("dark_forest", 512, 512, 1, 1);	
	m_collisionRect = CollisionRectangle(0,0, 0, 0);
}


DarkForest::~DarkForest(void)
{
}
