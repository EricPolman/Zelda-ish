#pragma once
#include "entity.h"
class SwordSlash :
	public Entity
{
public:
	SwordSlash(Direction a_direction, float a_fX = 0, float a_fY = 0); 
	~SwordSlash(void);

	void Hit(Entity* a_pOther, CollisionInfo a_info);
};

