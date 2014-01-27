#include "TriggerHomeCave.h"
#include "TileManager.h"


TriggerHomeCave::~TriggerHomeCave(void)
{
}


bool TriggerHomeCave::OnTriggerEnter()
{
	Tiles->SetRoom(41);
	m_pPlayer->SetPosition(Vector2(233, 313));
	return false;
}


bool TriggerHomeCave::OnTriggerStay()
{
	return true;
}


bool TriggerHomeCave::OnTriggerExit()
{
	return true;
}