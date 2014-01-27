#pragma once
#include "trigger.h"
class TriggerHomeCaveExit :
	public Trigger
{
public:
	TriggerHomeCaveExit(float a_fX, float a_fY) : Trigger(a_fX, a_fY) {}
	~TriggerHomeCaveExit(void);
	
	bool OnTriggerEnter();
	bool OnTriggerStay();
	bool OnTriggerExit();
};

