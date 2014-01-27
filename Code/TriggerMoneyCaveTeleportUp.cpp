#include "TriggerMoneyCaveTeleportUp.h"
#include "TileManager.h"


TriggerMoneyCaveTeleportUp::~TriggerMoneyCaveTeleportUp(void)
{
}


bool TriggerMoneyCaveTeleportUp::OnTriggerEnter()
{
	m_pPlayer->Move(0, -82);
	return true;
}


bool TriggerMoneyCaveTeleportUp::OnTriggerStay()
{
	return true;
}


bool TriggerMoneyCaveTeleportUp::OnTriggerExit()
{
	return true;
}