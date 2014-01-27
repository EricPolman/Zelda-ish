#pragma once
#include "trigger.h"
class TriggerMoneyCaveTeleportDown :
	public Trigger
{
public:
	TriggerMoneyCaveTeleportDown(float a_fX, float a_fY) : Trigger(a_fX, a_fY) {}
	~TriggerMoneyCaveTeleportDown(void);
	
	bool OnTriggerEnter();
	bool OnTriggerStay();
	bool OnTriggerExit();
};

