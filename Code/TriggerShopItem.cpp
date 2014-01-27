#include "TriggerShopItem.h"

TriggerShopItem::~TriggerShopItem(void)
{
}


bool TriggerShopItem::OnTriggerEnter()
{
	return true;
}


bool TriggerShopItem::OnTriggerStay()
{
	if(Input->IsKeyPressed(SDLK_q))
	{
		m_pItem->Buy(m_pPlayer);
	}
	return true;
}


bool TriggerShopItem::OnTriggerExit()
{
	return true;
}