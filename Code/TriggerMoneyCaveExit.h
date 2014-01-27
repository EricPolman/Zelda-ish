#pragma once
#include "trigger.h"
class TriggerMoneyCaveExit :
	public Trigger
{
public:
	TriggerMoneyCaveExit(float a_fX, float a_fY) : Trigger(a_fX, a_fY) {}
	~TriggerMoneyCaveExit(void);
	
	bool OnTriggerEnter();
	bool OnTriggerStay();
	bool OnTriggerExit();
};

