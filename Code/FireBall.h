#pragma once
#include "entity.h"

class FireBall :
	public Entity
{
public:
	FireBall(Vector2 a_shootDirection, float a_fX = 0, float a_fY = 0, Room* a_room = 0);
	~FireBall(void);
	
	void Hit(Entity* a_pOther, CollisionInfo a_info);
	void Update(float a_fDeltaTime);

	Vector2 m_shootDirection;
};

