#pragma once
#include "entity.h"

class Heart :
	public Entity
{
public:
	Heart(float a_fX = 0, float a_fY = 0, Room* a_room = 0);
	~Heart(void);
	
	virtual void Hit(Entity* a_pOther, CollisionInfo a_info);
};

