#pragma once
#include "entity.h"
class Guard :
	public Entity
{
public:
	Guard(float a_fX, float a_fY, Direction a_direction, Room* a_room);
	~Guard(void);

	Direction m_direction;
};

