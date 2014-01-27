#pragma once
#include "includes.h"
#include "Player.h"

class Trigger
{
public:
	Trigger(float a_fX, float a_fY);
	virtual ~Trigger(void){}
	
	virtual bool Update(float a_fDeltaTime, Player* a_player)
	{
		m_pPlayer = a_player;
		bool oldIfPlayerInTrigger = m_bPlayerInTrigger;
		CollisionRectangle playerRectangle = CollisionRectangle(
				a_player->GetPosition().x + a_player->m_velocity.x + a_player->m_collisionRect.x,
				a_player->GetPosition().y + a_player->m_velocity.y + a_player->m_collisionRect.y,
				a_player->m_collisionRect.width,
				a_player->m_collisionRect.height);
		CollisionInfo info = m_collisionRectangle.Intersects(playerRectangle);
		if(info.isColliding)
		{
			m_bPlayerInTrigger = true;
			if(!oldIfPlayerInTrigger)
			{
				if(!OnTriggerEnter())
				{
					return false;
				}
			}
			else
			{
				if(!OnTriggerStay())
				{
					return false;
				}
			}
		}
		else
		{
			m_bPlayerInTrigger = false;
			if(oldIfPlayerInTrigger)
			{
				if(!OnTriggerExit())
				{
					return false;
				}
			}
		}
		return true;
	}
	virtual bool OnTriggerEnter() = 0;
	virtual bool OnTriggerStay() = 0;
	virtual bool OnTriggerExit() = 0;

	bool m_bPlayerInTrigger;
	Player* m_pPlayer;
	
	CollisionRectangle m_collisionRectangle;
};

