#pragma once
#include "entity.h"

enum Item{ITEM_HEART, ITEM_WEAPONS, ITEM_BOMBS};

class ShopItem :
	public Entity
{
public:
	ShopItem(Item a_item, int a_cost, float a_fX = 0, float a_fY = 0, Room* a_room = 0);
	~ShopItem(void);
	
	void Update(float a_fDeltaTime);
	void Hit(Entity* a_pOther, CollisionInfo a_info);
	void Draw(Tmpl8::Surface* a_screen, Vector2 a_origin);
	bool m_bIsBought;
	float m_fShowRewardTimer;

	int m_iCost;
	Item m_item;

	std::string m_sCostString;

	void Buy(Entity* a_pPlayer);

	Tmpl8::Surface* m_pContents;

private:
	Tmpl8::Surface* m_pSurface;
};

