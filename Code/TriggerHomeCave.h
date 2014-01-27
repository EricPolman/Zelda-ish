#pragma once
#include "trigger.h"
class TriggerHomeCave :
	public Trigger
{
public:
	TriggerHomeCave(float a_fX, float a_fY) : Trigger(a_fX, a_fY) {}
	~TriggerHomeCave(void);
	
	bool OnTriggerEnter();
	bool OnTriggerStay();
	bool OnTriggerExit();
};

