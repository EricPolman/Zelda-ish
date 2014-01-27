#pragma once
#include "entity.h"
#include "Player.h"

enum EnemyType{GREEN_SOLDIER, RED_GORIYA, GREEN_GORIYA};
enum EnemyState{ENEMY_ATTACKING, ENEMY_WALKING, ENEMY_STUNNED, ENEMY_LOOKING_AROUND, ENEMY_IDLE};

class Enemy :
	public Entity
{
public:
	Enemy(EnemyType a_type, Direction a_direction, float a_fX = 0, float a_fY = 0, Room* a_room = 0);

	EnemyType m_enemyType;
	virtual ~Enemy(void);

	virtual void Update(float a_fDeltaTime);
	//virtual void Draw(Tmpl8::Surface* a_screen, Vector2 a_origin);
	virtual void Hit(Entity* a_pOther, CollisionInfo a_info);
	static Player* g_pPlayer;

	int m_iHealth;

	Direction m_spriteWalkDirection;

	EnemyState m_enemyState;

	float m_distanceTraveledInDirection;
	float m_maxDistance;

protected:
	float m_fInvulnerabilityTimer;
	float INVULNERABLE_TIME;
	bool m_bInvulnerable;
	bool m_bLookedAround;
	float m_fStunTimer;
	void ChangeDirection(Direction a_direction);
};

