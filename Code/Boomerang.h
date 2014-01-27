#pragma once
#include "Entity.h"

class Boomerang
	: public Entity
{
public:
	Boomerang(float a_fX, float a_fY, Vector2 a_direction, Entity* a_player);
	~Boomerang(void);
	
	void Update(float a_fDeltaTime);
	void Hit(Entity* a_pOther, CollisionInfo a_info);

	float m_fDistanceTraveled;
	bool m_bReturnToSender;

	Vector2 m_direction;
	Entity* m_player;
	void HitWall();
};

