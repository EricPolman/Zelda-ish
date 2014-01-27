#include "TriggerMoneyCaveTeleportDown.h"
#include "TileManager.h"


TriggerMoneyCaveTeleportDown::~TriggerMoneyCaveTeleportDown(void)
{
}


bool TriggerMoneyCaveTeleportDown::OnTriggerEnter()
{
	m_pPlayer->Move(0, 85);
	return true;
}


bool TriggerMoneyCaveTeleportDown::OnTriggerStay()
{
	return true;
}


bool TriggerMoneyCaveTeleportDown::OnTriggerExit()
{
	return true;
}