#include "TriggerChest.h"

TriggerChest::~TriggerChest(void)
{
}


bool TriggerChest::OnTriggerEnter()
{
	return true;
}


bool TriggerChest::OnTriggerStay()
{
	if(Input->IsKeyPressed(SDLK_q))
	{
		if(m_pChest != 0)
			m_pChest->Open(m_pPlayer);
		else
			m_pChestBig->Open(m_pPlayer);
	}
	return true;
}


bool TriggerChest::OnTriggerExit()
{
	return true;
}