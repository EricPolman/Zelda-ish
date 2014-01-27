#pragma once
#include "trigger.h"
#include "ShopItem.h"

class TriggerShopItem :
	public Trigger
{
public:
	TriggerShopItem(float a_fX, float a_fY) : Trigger(a_fX, a_fY) {}
	~TriggerShopItem(void);
	
	bool OnTriggerEnter();
	bool OnTriggerStay();
	bool OnTriggerExit();

	ShopItem* m_pItem;
};

