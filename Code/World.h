#pragma once
#include "includes.h"
#include "EntityManager.h"
#include "Guard.h"
#include "DarkForest.h"
#include "Aganihm.h"

enum WorldState{NORMAL, IN_TRANSITION};

class World
{
public:
	World(void);
	~World(void);

	void Init();
	void Update(float a_fDeltaTime);
	void Draw(Tmpl8::Surface* a_screen);
	void TestCollisions();

	Vector2 m_origin;
	Vector2 m_cameraPosition;
	Tmpl8::Surface* m_pWorldSurface;
	static Tmpl8::Surface* g_pScreen;

	int m_iCurrentRoom;
	float m_fTransitionTimer;

	void ChangeRoom(Entity* m_pPlayer, short direction);
	int m_iNextRoom;
	WorldState m_state;

	Guard* m_pBossGuard;
	DarkForest* m_pDarkForest;
	Aganihm* m_pAganihm;
	bool m_bBossSpawned, m_bBossDead;

	void SetState(WorldState a_state);

	void PlacePlayer();
	void PrepareEndGame();
	void EndGame();
private:
	CollisionRectangle GetTilesToCollideWith(CollisionRectangle a_ownRectangle);

	void PlaceGuards();
	void PlaceSoldiers();
	void PlaceTriggers();
	void PlaceOtherEntities();
	
};
