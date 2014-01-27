#pragma once
#include "trigger.h"
class TriggerMoneyCaveTeleportUp :
	public Trigger
{
public:
	TriggerMoneyCaveTeleportUp(float a_fX, float a_fY) : Trigger(a_fX, a_fY) {}
	~TriggerMoneyCaveTeleportUp(void);
	
	bool OnTriggerEnter();
	bool OnTriggerStay();
	bool OnTriggerExit();
};

