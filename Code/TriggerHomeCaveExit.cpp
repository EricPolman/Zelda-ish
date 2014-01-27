#include "TriggerHomeCaveExit.h"
#include "TileManager.h"


TriggerHomeCaveExit::~TriggerHomeCaveExit(void)
{
}


bool TriggerHomeCaveExit::OnTriggerEnter()
{
	Tiles->SetRoom(1);
	m_pPlayer->SetPosition(Vector2(168, 196));
	return false;
}


bool TriggerHomeCaveExit::OnTriggerStay()
{
	return true;
}


bool TriggerHomeCaveExit::OnTriggerExit()
{
	return true;
}