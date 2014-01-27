#pragma once
#include "Entity.h"
#include "World.h"
#include "SwordSlash.h"
#include "Boomerang.h"

enum PlayerState {PLAYER_ATTACKING, PLAYER_WALKING, PLAYER_IDLE, PLAYER_THROWING_BOOMERANG };

class Player : public Entity
{
public:
	Player(std::string a_tilesheetName, float a_fX = 0, float a_fY = 0);
	virtual ~Player();
	
	virtual void Update(float a_fDeltaTime);
	void UpdateDirectionReset();
	
	void SetDirection(Direction a_direction){m_direction = a_direction;}
	inline Direction GetDirection(){return m_direction;}

	void AddRupees(int a_iAmount);
	void DecreaseHealth(int a_iAmount);
	
	int GetHealth() {return m_iHealth;}
	int GetRupees() {return m_iRupees;}
	
	void EnableWeapons(){m_bHasSwordAndShield = true;}
	void EnableBoomerang();
	void DeleteBoomerang(){m_pCurrentBoomerang->m_state = REMOVED; m_pCurrentBoomerang = 0;}
	bool HasWeapons(){ return m_bHasSwordAndShield; }
	void KnockBack(Vector2 a_otherPosition);

	World* m_pWorld; 

	void Hit(Entity* a_pOther, CollisionInfo a_info);
	void Spawn();
 
	Boomerang* m_pCurrentBoomerang;
private:
	Direction m_direction;
	void ChangeDirection(Direction a_direction);
	bool m_bDirectionChanged;
	void Slash();
	void ThrowBoomerang();
	PlayerState m_playerState;
	
	float m_fRespawnTimer;
	float m_fInvulnerabilityTimer;
	float INVULNERABLE_TIME;
	bool m_bInvulnerable;


	int m_iHealth;
	int m_iRupees;

	void Die();
	
	bool m_bHasBoomerang;
	bool m_bHasSwordAndShield;

	SwordSlash* m_pCurrentSwordSlash;
};
