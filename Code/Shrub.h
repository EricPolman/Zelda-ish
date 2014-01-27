#pragma once
#include "entity.h"

class Shrub :
	public Entity
{
public:
	Shrub(float a_fX = 0, float a_fY = 0, Room* a_room = 0);
	~Shrub(void);
	
	virtual void Hit(Entity* a_pOther, CollisionInfo a_info);
};

