#pragma once
#include "entity.h"

class Lightning :
	public Entity
{
public:
	Lightning(float a_fX = 0, float a_fY = 0, Room* a_room = 0);
	~Lightning(void);
	
	void Hit(Entity* a_pOther, CollisionInfo a_info);
	void Update(float a_fDeltaTime);
};

