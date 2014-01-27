#include "TriggerMoneyCaveExit.h"
#include "TileManager.h"


TriggerMoneyCaveExit::~TriggerMoneyCaveExit(void)
{
}


bool TriggerMoneyCaveExit::OnTriggerEnter()
{
	Tiles->SetRoom(14);
	m_pPlayer->SetPosition(Vector2(249, 209));
	return false;
}


bool TriggerMoneyCaveExit::OnTriggerStay()
{
	return true;
}


bool TriggerMoneyCaveExit::OnTriggerExit()
{
	return true;
}