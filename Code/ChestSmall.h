#pragma once
#include "entity.h"

class ChestSmall :
	public Entity
{
public:
	ChestSmall(float a_fX = 0, float a_fY = 0, Room* a_room = 0);
	~ChestSmall(void);
	
	virtual void Update(float a_fDeltaTime);
	virtual void Hit(Entity* a_pOther, CollisionInfo a_info);
	virtual void Draw(Tmpl8::Surface* a_screen, Vector2 a_origin);
	bool m_bIsOpened;
	bool m_bRewardShown;
	float m_fShowRewardTimer;

	void Open(Entity* a_pPlayer);

	Tmpl8::Surface* m_pContents;
};

