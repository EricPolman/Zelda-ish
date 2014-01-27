#include "TriggerMoneyCave.h"
#include "TileManager.h"


TriggerMoneyCave::~TriggerMoneyCave(void)
{
}


bool TriggerMoneyCave::OnTriggerEnter()
{
	Tiles->SetRoom(47);
	m_pPlayer->SetPosition(Vector2(233, 448));
	return false;
}


bool TriggerMoneyCave::OnTriggerStay()
{
	return true;
}


bool TriggerMoneyCave::OnTriggerExit()
{
	return true;
}