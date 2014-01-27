#pragma once
#include "entity.h"

class Rupee :
	public Entity
{
public:
	Rupee(float a_fX = 0, float a_fY = 0, Room* a_room = 0);
	~Rupee(void);
	
	virtual void Hit(Entity* a_pOther, CollisionInfo a_info);
};

