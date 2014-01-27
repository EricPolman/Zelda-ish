#pragma once
#include "entity.h"

enum BossState{BOSS_IDLE, BOSS_HIT, BOSS_DYING, BOSS_STUNNED, BOSS_ATTACKING, BOSS_TELEPORTING};

class Aganihm :
	public Entity
{
public:
	Aganihm(float a_fX, float a_fY, Room* a_room);
	~Aganihm(void);

	Direction m_direction;

	Entity* m_pPlayer;

	void Update(float a_fDeltaTime);
	void Hit(Entity* a_pOther, CollisionInfo a_info);
	BossState m_bossState;
private:
	void Zap();
	void ShootBall();
	float m_fStunTimer;
	float m_fInvulnerabilityTimer;
	float INVULNERABLE_TIME;
	bool m_bInvulnerable;
	bool m_bAttackFired;

	float m_fAttackTimer;
	bool m_bCanAttack;
	
	float m_fTeleportTimer;
	bool m_bCanTeleport;
	Vector2 m_teleportPositions[6];


	int m_iHealth;
};

