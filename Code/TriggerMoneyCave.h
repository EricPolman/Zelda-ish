#pragma once
#include "trigger.h"
class TriggerMoneyCave :
	public Trigger
{
public:
	TriggerMoneyCave(float a_fX, float a_fY) : Trigger(a_fX, a_fY) {}
	~TriggerMoneyCave(void);
	
	bool OnTriggerEnter();
	bool OnTriggerStay();
	bool OnTriggerExit();
};

