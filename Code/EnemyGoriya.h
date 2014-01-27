#pragma once
#include "enemy.h"
class EnemyGoriya :
	public Enemy
{
public:
	EnemyGoriya(EnemyType a_type, Direction a_direction, float a_fX, float a_fY, Room* a_room);
	virtual ~EnemyGoriya(void);
	
	virtual void Update(float a_fDeltaTime);
	
	bool m_bDirectionChanged;
	bool m_bInverseMovement;
	Direction m_direction;
	void ChangeDirection(Direction a_direction);
};

