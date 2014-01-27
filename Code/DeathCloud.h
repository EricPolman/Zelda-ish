#pragma once
#include "entity.h"
class DeathCloud :
	public Entity
{
public:
	DeathCloud(Entity* a_owner, float a_fX = 0, float a_fY = 0);
	~DeathCloud(void);
	Entity* m_owner;

	void Update(float a_fDeltaTime);
};

