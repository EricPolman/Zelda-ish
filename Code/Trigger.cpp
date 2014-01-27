#include "Trigger.h"


Trigger::Trigger(float a_fX, float a_fY){
	m_collisionRectangle.x = a_fX; m_collisionRectangle.y = a_fY;
	m_collisionRectangle.width = 1; m_collisionRectangle.height = 1;
	m_bPlayerInTrigger = false;
}