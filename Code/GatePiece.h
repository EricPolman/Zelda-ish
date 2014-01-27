#pragma once
#include "entity.h"
class GatePiece :
	public Entity
{
public:
	GatePiece(Direction a_side, float a_fX = 0, float a_fY = 0, Room* a_room = 0);
	~GatePiece(void);
};

