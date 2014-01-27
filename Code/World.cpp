#include "World.h"
#include "TileManager.h"
#include "Enemy.h"
#include "TextureManager.h"
#include "TriggerManager.h"
#include "Boomerang.h"
#include "EnemyGoriya.h"
#include "TriggerHomeCave.h"
#include "TriggerHomeCaveExit.h"
#include "TriggerMoneyCave.h"
#include "TriggerMoneyCaveExit.h"
#include "TriggerMoneyCaveTeleportUp.h"
#include "TriggerMoneyCaveTeleportDown.h"
#include "ChestSmall.h"
#include "UserInterface.h"
#include "GatePiece.h"
#include "ShopItem.h"
#include "ShopOwner.h"
#include "ChestBig.h"

UserInterface* m_pUserInterface = 0;
Tmpl8::Surface* World::g_pScreen = 0;

World::World(void)
{
	m_origin = Vector2(0,0);
	m_cameraPosition = -Vector2(SCRWIDTH/2, SCRHEIGHT/2);
	m_pWorldSurface = new Tmpl8::Surface(ROOM_WIDTH, ROOM_HEIGHT);
	m_state = NORMAL;
	m_fTransitionTimer = 0;
	g_pScreen = 0;
	m_pAganihm = 0;
	m_bBossSpawned = false;
	m_bBossDead = false;
}


World::~World(void)
{
}


void World::Init()
{
	Textures->Add("player", "assets/sprites/player.png");
	Textures->Add("enemy_one", "assets/sprites/enemy_one.png");
	Textures->Add("blank", "assets/sprites/blank.png");
	Textures->Add("shrub", "assets/sprites/shrub.png");
	Textures->Add("deathCloud", "assets/sprites/deathCloud.png");
	Textures->Add("boomerang", "assets/sprites/boomerang.png");
	Textures->Add("guard", "assets/sprites/guards.png");
	Textures->Add("chest_small", "assets/sprites/chest_small.png");
	Textures->Add("rupee_red_chest", "assets/sprites/rupee_red_chest.png");
	Textures->Add("gate_left", "assets/sprites/gate_left.png");
	Textures->Add("gate_right", "assets/sprites/gate_right.png");
	Textures->Add("item_weapons", "assets/sprites/item_weapons.png");
	Textures->Add("shopowner", "assets/sprites/shopowner.png");
	Textures->Add("chest_big", "assets/sprites/chest_large.png");
	Textures->Add("boomerang_unlock", "assets/sprites/boomerang_unlock.png");
	Textures->Add("goriya_red", "assets/sprites/goriya_red.png");
	Textures->Add("goriya_green", "assets/sprites/goriya_green.png");
	Textures->Add("rupee_pickup", "assets/sprites/rupee_pickup.png");
	Textures->Add("dark_forest", "assets/sprites/darkwood_noclouds.png");
	Textures->Add("aganihm", "assets/sprites/aganihm.png");
	Textures->Add("lightning", "assets/sprites/lightning.png");
	Textures->Add("fireball", "assets/sprites/fireball.png");
	Textures->Add("heart_pickup", "assets/sprites/heart_pickup.png");


	std::ifstream ifile("assets/tilesets/metadata.dat");
	if (ifile) {
		ifile.close();
		Tiles->LoadExistingMap();
	}
	else
	{
		Tiles->LoadBaseSprite("assets/backgrounds/light_world-1.png");
		Tiles->ProcessTileMap();
	}
	Tiles->m_pWorld = this;
	Tiles->SetRoom(1);

	Player* player = new Player("player",168,204);
	Enemy::g_pPlayer = player;
	player->m_pWorld = this;

	Entities->SetPlayer(player);
	Triggers->m_player = player;

	m_pUserInterface = new UserInterface();
	m_pUserInterface->SetPlayer(player);
	
	PlaceGuards();
	PlaceSoldiers();
	PlaceTriggers();
	PlaceOtherEntities();
	Entities->PushQueues();
	//PrepareEndGame();
	player->Spawn();
}


void World::Update(float a_fDeltaTime)
{
	Tiles->Update(a_fDeltaTime);
	if(m_state == NORMAL)
	{
		Entities->Update(a_fDeltaTime, Tiles->GetCurrentRoom());
		m_cameraPosition.x = Entities->m_pCameraCenter->GetPosition().x + Entities->m_pCameraCenter->GetSprite()->m_textureRect.width - SCRWIDTH/2;
		m_cameraPosition.y = Entities->m_pCameraCenter->GetPosition().y + Entities->m_pCameraCenter->GetSprite()->m_textureRect.height - SCRHEIGHT/2;

		if(m_cameraPosition.x < 0)
		{
			m_cameraPosition.x = 0;
		}
		else if(m_cameraPosition.x + SCRWIDTH > ROOM_WIDTH)
		{
			m_cameraPosition.x =  ROOM_WIDTH - SCRWIDTH;
		}
		if(m_cameraPosition.y < 0)
		{
			m_cameraPosition.y = 0;
		}
		else if(m_cameraPosition.y + SCRHEIGHT > ROOM_HEIGHT)
		{
			m_cameraPosition.y = ROOM_HEIGHT - SCRHEIGHT;
		}

		TestCollisions();
		Triggers->Update(a_fDeltaTime);
	}
	else
	{
		if(((Player*)(Entities->m_pCameraCenter))->m_pCurrentBoomerang != 0)
		{
			((Player*)(Entities->m_pCameraCenter))->DeleteBoomerang();
		}
		((Player*)(Entities->m_pCameraCenter))->UpdateDirectionReset();
		m_fTransitionTimer += a_fDeltaTime * SCROLL_SPEED;
		if(m_iCurrentRoom + 1 == m_iNextRoom) //Next screen is below current screen
		{
			float newYPos = max(ROOM_HEIGHT - m_fTransitionTimer * ROOM_HEIGHT - 12, -12);
			Entities->m_pCameraCenter->SetPosition(Vector2(Entities->m_pCameraCenter->GetPosition().x, newYPos));
			
			m_cameraPosition.y -= a_fDeltaTime * (ROOM_HEIGHT - SCRHEIGHT) * SCROLL_SPEED;
		}
		else if(m_iCurrentRoom - 1 == m_iNextRoom) //Next screen is above current screen
		{
			float newYPos = min(m_fTransitionTimer * ROOM_HEIGHT, ROOM_HEIGHT - 36);
			Entities->m_pCameraCenter->SetPosition(Vector2(Entities->m_pCameraCenter->GetPosition().x, newYPos));

			m_cameraPosition.y += a_fDeltaTime * (ROOM_HEIGHT - SCRHEIGHT) * SCROLL_SPEED;
		}
		else if(m_iNextRoom > m_iCurrentRoom) //Next screen is to the right of current screen
		{
			float newXPos = max(ROOM_WIDTH - m_fTransitionTimer * ROOM_WIDTH - 12, -12);
			Entities->m_pCameraCenter->SetPosition(Vector2(newXPos, Entities->m_pCameraCenter->GetPosition().y));
			
			m_cameraPosition.x -= a_fDeltaTime * (ROOM_WIDTH - SCRWIDTH) * SCROLL_SPEED;
		}
		else if(m_iNextRoom < m_iCurrentRoom) //Next screen is to the left of current screen
		{
			float newXPos = min(m_fTransitionTimer * ROOM_WIDTH, ROOM_WIDTH - 36);
			Entities->m_pCameraCenter->SetPosition(Vector2(newXPos, Entities->m_pCameraCenter->GetPosition().y));
			
			m_cameraPosition.x += a_fDeltaTime * (ROOM_WIDTH - SCRWIDTH) * SCROLL_SPEED;
		}
	}
}

	
void World::Draw(Tmpl8::Surface* a_screen)
{
	if(g_pScreen == 0)
	{
		g_pScreen = a_screen;
	}
	m_pWorldSurface->Clear(0);

	Tiles->Draw(m_pWorldSurface);
	//Entities->Draw(m_pWorldSurface, m_origin, Tiles->GetCurrentRoom());

	if(m_state == IN_TRANSITION)
	{
		if(m_iCurrentRoom + 1 == m_iNextRoom) //Next screen is below current screen
		{	
			for(std::vector<Entity*>::iterator i = Entities->GetEntities(Tiles->GetCurrentRoom())->begin(); i != Entities->GetEntities(Tiles->GetCurrentRoom())->end(); i++)
			{
				if((*i)->m_type != PLAYER)
					(*i)->Draw(m_pWorldSurface, m_origin + Vector2(0, -m_fTransitionTimer * ROOM_HEIGHT));
			}
			for(std::vector<Entity*>::iterator i = Entities->GetEntities(Tiles->GetRoom(m_iNextRoom))->begin(); i != Entities->GetEntities(Tiles->GetRoom(m_iNextRoom))->end(); i++)
			{
				if((*i)->m_type != PLAYER)
					(*i)->Draw(m_pWorldSurface, m_origin + Vector2(0, ROOM_HEIGHT - m_fTransitionTimer * ROOM_HEIGHT));
			}
		}
		else if(m_iCurrentRoom - 1 == m_iNextRoom) //Next screen is above current screen
		{
			for(std::vector<Entity*>::iterator i = Entities->GetEntities(Tiles->GetCurrentRoom())->begin(); i != Entities->GetEntities(Tiles->GetCurrentRoom())->end(); i++)
			{
				if((*i)->m_type != PLAYER)
					(*i)->Draw(m_pWorldSurface, m_origin + Vector2(0, m_fTransitionTimer * ROOM_HEIGHT));
			}
			for(std::vector<Entity*>::iterator i = Entities->GetEntities(Tiles->GetRoom(m_iNextRoom))->begin(); i != Entities->GetEntities(Tiles->GetRoom(m_iNextRoom))->end(); i++)
			{
				if((*i)->m_type != PLAYER)
					(*i)->Draw(m_pWorldSurface, m_origin + Vector2(0, -ROOM_HEIGHT + m_fTransitionTimer * ROOM_HEIGHT));
			}
		}
		else if(m_iNextRoom > m_iCurrentRoom) //Next screen is to the right of current screen
		{
			for(std::vector<Entity*>::iterator i = Entities->GetEntities(Tiles->GetCurrentRoom())->begin(); i != Entities->GetEntities(Tiles->GetCurrentRoom())->end(); i++)
			{
				if((*i)->m_type != PLAYER)
					(*i)->Draw(m_pWorldSurface, m_origin + Vector2(-m_fTransitionTimer * ROOM_HEIGHT, 0));
			}
			for(std::vector<Entity*>::iterator i = Entities->GetEntities(Tiles->GetRoom(m_iNextRoom))->begin(); i != Entities->GetEntities(Tiles->GetRoom(m_iNextRoom))->end(); i++)
			{
				if((*i)->m_type != PLAYER)
					(*i)->Draw(m_pWorldSurface, m_origin + Vector2(ROOM_HEIGHT - m_fTransitionTimer * ROOM_HEIGHT, 0));
			}
		}
		else if(m_iNextRoom < m_iCurrentRoom) //Next screen is to the left of current screen
		{
			for(std::vector<Entity*>::iterator i = Entities->GetEntities(Tiles->GetCurrentRoom())->begin(); i != Entities->GetEntities(Tiles->GetCurrentRoom())->end(); i++)
			{
				if((*i)->m_type != PLAYER)
					(*i)->Draw(m_pWorldSurface, m_origin + Vector2(m_fTransitionTimer * ROOM_HEIGHT, 0));
			}
			for(std::vector<Entity*>::iterator i = Entities->GetEntities(Tiles->GetRoom(m_iNextRoom))->begin(); i != Entities->GetEntities(Tiles->GetRoom(m_iNextRoom))->end(); i++)
			{
				if((*i)->m_type != PLAYER)
					(*i)->Draw(m_pWorldSurface, m_origin + Vector2(-ROOM_HEIGHT + m_fTransitionTimer * ROOM_HEIGHT, 0));
			}
		}

		Entities->m_pCameraCenter->Draw(m_pWorldSurface, m_origin);
	}
	else
	{
		Entities->Draw(m_pWorldSurface, m_origin, Tiles->GetCurrentRoom());
		if(Tiles->GetCurrentRoom() == Tiles->GetRoom(16))
		{
			if(m_pBossGuard != 0)
			{
				UserInterface::DrawText("THERE IS A DARK PRESENCE IN THIS", m_pBossGuard->GetPosition().x - 90, m_pBossGuard->GetPosition().y - 45);
				UserInterface::DrawText("FOREST AND YOU'RE TOO WEAK TO FIGHT IT!", m_pBossGuard->GetPosition().x - 90, m_pBossGuard->GetPosition().y - 35);
				UserInterface::DrawText("WE'RE ALREADY LOOKING FOR A WEAPON IN THE", m_pBossGuard->GetPosition().x - 90, m_pBossGuard->GetPosition().y - 25);
				UserInterface::DrawText("DESERT TO THE SOUTH. WE'LL GET RID OF THIS EVIL!", m_pBossGuard->GetPosition().x - 90, m_pBossGuard->GetPosition().y - 15);
			}
		}
		if(m_bBossSpawned)
		{
			if(m_bBossDead)
			{
				if(Tiles->GetCurrentRoom() == Tiles->GetRoom(15))
				{
					UserInterface::DrawText("CONGRATULATIONS!", 180,100);
					UserInterface::DrawText("YOU HAVE FINISHED THE GAME.", 180,110);
				}
			}
			else
			{
				if(m_pAganihm != 0)
				{
					if(m_pAganihm->m_state == REMOVED)
					{
						m_pAganihm = 0;
						m_bBossDead = true;
						EndGame();
					}
				}
			}
		}
	}

	m_pWorldSurface->CopyTo(a_screen, -m_origin.x - m_cameraPosition.x,-m_origin.y - m_cameraPosition.y);
	m_pUserInterface->Draw(a_screen);
}


void World::ChangeRoom(Entity* a_pPlayer, short direction)
{
	int newRoom = m_iCurrentRoom;
	switch(direction)
	{
	case 0:
		newRoom += 1;
		//a_pPlayer->SetPosition(Vector2(a_pPlayer->GetPosition().x, 0));
		break;
	case 1:
		newRoom += ROWS_OF_ROOMS;
		//a_pPlayer->SetPosition(Vector2(0, a_pPlayer->GetPosition().y));
		break;
	case 2:
		newRoom -= 1;
		//a_pPlayer->SetPosition(Vector2(a_pPlayer->GetPosition().x, ROOM_HEIGHT - a_pPlayer->GetSprite()->GetHeight()));
		break;
	case 3:
		newRoom -= ROWS_OF_ROOMS;
		//a_pPlayer->SetPosition(Vector2(ROOM_WIDTH - a_pPlayer->GetSprite()->GetWidth(), a_pPlayer->GetPosition().y));
		break;
	}

	if(newRoom < 0 || newRoom > ROWS_OF_ROOMS * COLS_OF_ROOMS)
	{
		return;
	}

	m_iNextRoom = newRoom;
	SetState(IN_TRANSITION);
	//Tiles->SetRoom(newRoom);
}


void World::SetState(WorldState a_state)
{
	if(m_state == IN_TRANSITION)
	{
		Tiles->SetRoom(m_iNextRoom);
		m_fTransitionTimer = 0;
	}

	m_state = a_state;
}


void World::TestCollisions()
{
	for(std::vector<Entity*>::iterator iter = Entities->GetEntities(Tiles->GetCurrentRoom())->begin(); iter != Entities->GetEntities(Tiles->GetCurrentRoom())->end(); iter++)
	{
		CollisionRectangle entityRectangle = CollisionRectangle(
				(*iter)->GetPosition().x + (*iter)->m_velocity.x + (*iter)->m_collisionRect.x,
				(*iter)->GetPosition().y + (*iter)->m_velocity.y + (*iter)->m_collisionRect.y,
				(*iter)->m_collisionRect.width,
				(*iter)->m_collisionRect.height);
		if((*iter)->m_bCollidesWithTiles)
		{
			Vector2 displacement(0,0);
			CollisionRectangle tilesToCollideWith = GetTilesToCollideWith(entityRectangle);
			int lastTile = (tilesToCollideWith.y + tilesToCollideWith.height) * COLS_OF_TILES + (tilesToCollideWith.x + tilesToCollideWith.width);
			for(int y = tilesToCollideWith.y; y < tilesToCollideWith.y + tilesToCollideWith.height; y++)
			{
				for(int x = tilesToCollideWith.x; x < tilesToCollideWith.x + tilesToCollideWith.width; x++)
				{
					if(y > 64)
					{
						break;
					}
					int i = y * COLS_OF_TILES + x;
					CollisionType colType = Tiles->GetTileSurface(Tiles->GetCurrentRoom()->m_tiles[i]->m_iTileId)->m_collisionType;
					if(colType == NONE || (colType == BOOMERANGABLE && (*iter)->m_type == PLAYER_WEAPON))
						continue;

					CollisionRectangle tileRectangle = CollisionRectangle(Tiles->GetCurrentRoom()->m_tiles[i]->m_collisionRectangle);
					CollisionInfo info = entityRectangle.Intersects(tileRectangle);

					if(info.isColliding)
					{
						if(abs(info.depth.x) > 4)
						{
							(*iter)->Move(info.depth.x / 30,0);
						}
						if(abs(info.depth.y) > 4)
						{
							(*iter)->Move(0,info.depth.y / 30);
						}
						info.depth.Normalize();
						info.depth = info.depth * 1.6f;
						
						//if(info.depth.x > 0 && (*iter)->m_velocity.x < 1 || info.depth.x < 0 && (*iter)->m_velocity.x > -1)
						//{
							(*iter)->m_velocity.x += info.depth.x * abs((*iter)->m_velocity.x + .05f);
						//}
						//if(info.depth.y > 0 && (*iter)->m_velocity.y < 1 || info.depth.y < 0 && (*iter)->m_velocity.y > -1)
						//{
							(*iter)->m_velocity.y += info.depth.y * abs((*iter)->m_velocity.y + .05f);
						//}
						if((*iter)->m_type == PLAYER_WEAPON)
						{
							((Boomerang*)(*iter))->HitWall();
						}
						else if((*iter)->m_type == BOSS && colType != BOOMERANGABLE)
						{
							(*iter)->m_state = REMOVED;
						}
					}
				}
			}
		}
		if((*iter)->m_type == DESTROYABLE || (*iter)->m_type == EFFECT)
			continue;

		for(std::vector<Entity*>::iterator otherIter = Entities->GetEntities(Tiles->GetCurrentRoom())->begin(); otherIter != Entities->GetEntities(Tiles->GetCurrentRoom())->end(); otherIter++)
		{
			if(*iter == *otherIter)
				continue;
			
			CollisionRectangle otherEntityRectangle = CollisionRectangle(
				(*otherIter)->GetPosition().x + (*otherIter)->m_velocity.x + (*otherIter)->m_collisionRect.x,
				(*otherIter)->GetPosition().y + (*otherIter)->m_velocity.y + (*otherIter)->m_collisionRect.y,
				(*otherIter)->m_collisionRect.width,
				(*otherIter)->m_collisionRect.height);

			CollisionInfo info = entityRectangle.Intersects(otherEntityRectangle);

			if(info.isColliding)
			{
				(*iter)->Hit(*otherIter, info);
			}
		}
	}
}


CollisionRectangle World::GetTilesToCollideWith(CollisionRectangle a_ownRectangle)
{
	int rectWidth = a_ownRectangle.width;
	int widthInTiles = 0;
	while(rectWidth > 0)
	{
		rectWidth -= TILE_WIDTH;
		widthInTiles++;
	}

	int rectHeight = a_ownRectangle.height;
	int heightInTiles = 0;
	while(rectHeight > 0)
	{
		rectHeight -= TILE_HEIGHT;
		heightInTiles++;
	}

	CollisionRectangle ownRectInTiles(a_ownRectangle.x / TILE_WIDTH, a_ownRectangle.y / TILE_WIDTH, widthInTiles , heightInTiles);
	CollisionRectangle bounds(ownRectInTiles.x - 3, ownRectInTiles.y - 3, 6, 6);
	while(bounds.x + bounds.width > COLS_OF_TILES)
	{
		bounds.width--;
	}
	while(bounds.y + bounds.height > ROWS_OF_TILES)
	{
		bounds.height--;
	}

	bounds.x = max(bounds.x, 0);
	bounds.y = max(bounds.y, 0);

	return bounds;
}


void World::PlaceGuards()
{
	new Guard(128, 16, DOWN, Tiles->GetRoom(1));
	new Guard(320, 16, DOWN, Tiles->GetRoom(1));

	new Guard(244, 16, DOWN, Tiles->GetRoom(7));
	new Guard(280, 16, DOWN, Tiles->GetRoom(7));
	new Guard(316, 16, DOWN, Tiles->GetRoom(7));
	
	new Guard(16, 448, RIGHT, Tiles->GetRoom(9));
	
	new Guard(464, 298, DOWN, Tiles->GetRoom(20));
	new Guard(490, 298, DOWN, Tiles->GetRoom(20));
	new Guard(0, 298, DOWN, Tiles->GetRoom(26));
	new Guard(30, 298, DOWN, Tiles->GetRoom(26));

	new Guard(480, 368, LEFT, Tiles->GetRoom(27));
	new Guard(480, 400, LEFT, Tiles->GetRoom(27));
	
	new Guard(464, 378, LEFT, Tiles->GetRoom(29));
	new Guard(464, 404, LEFT, Tiles->GetRoom(29));
	new Guard(464, 430, LEFT, Tiles->GetRoom(29));
	
	new Guard(290, 310, DOWN, Tiles->GetRoom(10));
	new Guard(96, 68, DOWN, Tiles->GetRoom(17));
	new Guard(370, 244, DOWN, Tiles->GetRoom(23));
	new Guard(385, 114, DOWN, Tiles->GetRoom(28));

	m_pBossGuard = new Guard(225, 65, DOWN, Tiles->GetRoom(16));
}


void World::PlaceSoldiers()
{
	/* Kakariko village */
	new Enemy(GREEN_SOLDIER, DOWN, 304, 304, Tiles->GetRoom(1));
	new Enemy(GREEN_SOLDIER, RIGHT, 296, 60, Tiles->GetRoom(1));
	new Enemy(GREEN_SOLDIER, UP, 450, 312, Tiles->GetRoom(1));
	new Enemy(GREEN_SOLDIER, RIGHT, 104, 444, Tiles->GetRoom(1));
	
	new Enemy(GREEN_SOLDIER, RIGHT, 130, 220, Tiles->GetRoom(2));
	new Enemy(GREEN_SOLDIER, UP, 294, 220, Tiles->GetRoom(2));
	new Enemy(GREEN_SOLDIER, DOWN, 105, 70, Tiles->GetRoom(2));
	new Enemy(GREEN_SOLDIER, LEFT, 494, 428, Tiles->GetRoom(2));
	
	new Enemy(GREEN_SOLDIER, DOWN, 326, 64, Tiles->GetRoom(7));
	new Enemy(GREEN_SOLDIER, DOWN, 408, 300, Tiles->GetRoom(7));
	new Enemy(GREEN_SOLDIER, UP, 223, 484, Tiles->GetRoom(7));
	new Enemy(GREEN_SOLDIER, RIGHT, 120, 60, Tiles->GetRoom(7));
	
	new Enemy(GREEN_SOLDIER, RIGHT, 34, 220, Tiles->GetRoom(8));
	new Enemy(GREEN_SOLDIER, LEFT, 408, 200, Tiles->GetRoom(8));
	new Enemy(GREEN_SOLDIER, UP, 16, 428, Tiles->GetRoom(8));
	new Enemy(GREEN_SOLDIER, DOWN, 408, 170, Tiles->GetRoom(8));
	Enemy* e = new Enemy(GREEN_SOLDIER, DOWN, 310, 225, Tiles->GetRoom(8));
	e->m_maxDistance = 100;
	/* End of Kakariko village */
	
	new Enemy(GREEN_SOLDIER, RIGHT, 178, 64, Tiles->GetRoom(9));
	new Enemy(GREEN_SOLDIER, RIGHT, 300, 400, Tiles->GetRoom(9));
	e = new Enemy(GREEN_SOLDIER, DOWN, 185, 325, Tiles->GetRoom(9));
	e->m_maxDistance = 100;
	
	e = new Enemy(GREEN_SOLDIER, RIGHT, 165, 230, Tiles->GetRoom(9));
	e->m_maxDistance = 40;

	e = new Enemy(GREEN_SOLDIER, UP, 184, 220, Tiles->GetRoom(5));
	e->m_maxDistance = 150;
	e = new Enemy(GREEN_SOLDIER, DOWN, 214, 220, Tiles->GetRoom(5));
	e->m_maxDistance = 150;
	e = new Enemy(GREEN_SOLDIER, UP, 244, 220, Tiles->GetRoom(5));
	e->m_maxDistance = 150;
	e = new Enemy(GREEN_SOLDIER, DOWN, 274, 220, Tiles->GetRoom(5));
	e->m_maxDistance = 150;
	e = new Enemy(GREEN_SOLDIER, UP, 304, 220, Tiles->GetRoom(5));
	e->m_maxDistance = 150;
	
	e = new Enemy(GREEN_SOLDIER, RIGHT, 318, 105, Tiles->GetRoom(5));
	e->m_maxDistance = 150;
	e = new Enemy(GREEN_SOLDIER, LEFT, 318, 135, Tiles->GetRoom(5));
	e->m_maxDistance = 150;
	
	new Enemy(GREEN_SOLDIER, DOWN, 322, 98, Tiles->GetRoom(27));
	new Enemy(GREEN_SOLDIER, LEFT, 322, 400, Tiles->GetRoom(27));
}


void World::PlaceTriggers()
{
	Triggers->Add(new TriggerMoneyCave(270, 228),Tiles->GetRoom(14));
	Triggers->Add(new TriggerMoneyCaveExit(256, 484),Tiles->GetRoom(47));
	Triggers->Add(new TriggerMoneyCaveTeleportUp(256, 300),Tiles->GetRoom(47));
	Triggers->Add(new TriggerMoneyCaveTeleportDown(256, 236),Tiles->GetRoom(47));

	Triggers->Add(new TriggerHomeCave(190, 210),Tiles->GetRoom(1));
	Triggers->Add(new TriggerHomeCaveExit(250, 360),Tiles->GetRoom(41));
	Triggers->Add(new TriggerHomeCaveExit(250, 360),Tiles->GetRoom(41));
}


void World::PlaceOtherEntities()
{
	new ChestSmall(240, 128, Tiles->GetRoom(47));
	new ChestSmall(256, 128, Tiles->GetRoom(47));
	new GatePiece(LEFT, 344, 416, Tiles->GetRoom(8));
	new GatePiece(RIGHT, 384, 416, Tiles->GetRoom(8));
	new ShopItem(ITEM_WEAPONS, 1000, 248, 240, Tiles->GetRoom(41));
	new ShopOwner(248, 192, (Player*)Entities->m_pCameraCenter, Tiles->GetRoom(41));
	new ChestBig(288, 384, Tiles->GetRoom(4));

	m_pDarkForest = new DarkForest();
}

void World::PlacePlayer()
{
	Tiles->SetRoom(41);
	Entities->m_pCameraCenter->SetPosition(Vector2(230,290));
}


void World::PrepareEndGame()
{
	m_pBossGuard->m_state = REMOVED;
	m_pBossGuard->m_bIsVisible = false;
	m_pBossGuard = 0;

	new EnemyGoriya(GREEN_GORIYA, DOWN, 100, 100, Tiles->GetRoom(11));
	
	new EnemyGoriya(RED_GORIYA, DOWN, 360, 190, Tiles->GetRoom(17));
	
	new EnemyGoriya(RED_GORIYA, DOWN, 265, 175, Tiles->GetRoom(23));
	new EnemyGoriya(GREEN_GORIYA, DOWN, 185, 370, Tiles->GetRoom(23));

	new EnemyGoriya(RED_GORIYA, DOWN, 172, 274, Tiles->GetRoom(28));
	new EnemyGoriya(RED_GORIYA, RIGHT, 260, 360, Tiles->GetRoom(28));
	new EnemyGoriya(GREEN_GORIYA, DOWN, 172, 360, Tiles->GetRoom(28));
	new EnemyGoriya(GREEN_GORIYA, RIGHT, 260, 274, Tiles->GetRoom(28));

	new Enemy(GREEN_SOLDIER, RIGHT, 184, 216, Tiles->GetRoom(16));
	new Enemy(GREEN_SOLDIER, RIGHT, 216, 216, Tiles->GetRoom(16));
	new Enemy(GREEN_SOLDIER, RIGHT, 248, 216, Tiles->GetRoom(16));
	new Enemy(GREEN_SOLDIER, RIGHT, 280, 216, Tiles->GetRoom(16));
	new Enemy(GREEN_SOLDIER, RIGHT, 302, 216, Tiles->GetRoom(16));

	m_pAganihm = new Aganihm(206,200,Tiles->GetRoom(15));
	m_pAganihm->m_pPlayer = Enemy::g_pPlayer;
	m_bBossSpawned = true;
	Entities->PushQueues();
}


void World::EndGame()
{
	m_pDarkForest->m_state = REMOVED;
	m_pDarkForest->m_bIsVisible = false;
	m_pDarkForest = 0;
}