#pragma once
#include "entity.h"
#include "Player.h"
class ShopOwner :
	public Entity
{
public:
	ShopOwner(float a_fX, float a_fY, Player* a_pPlayer, Room* a_room);
	~ShopOwner(void);
	
	Player* m_pPlayer;

	bool m_bIsVicky;

	void Update(float a_fDeltaTime);
};

