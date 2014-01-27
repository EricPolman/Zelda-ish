#pragma once
#include "trigger.h"
#include "ChestSmall.h"
#include "ChestBig.h"

class TriggerChest :
	public Trigger
{
public:
	TriggerChest(float a_fX, float a_fY) : Trigger(a_fX, a_fY) {m_pChest = 0; m_pChestBig = 0;}
	~TriggerChest(void);
	
	bool OnTriggerEnter();
	bool OnTriggerStay();
	bool OnTriggerExit();
	
	ChestSmall* m_pChest;
	ChestBig* m_pChestBig;
};

