#include "DeathCloud.h"
#include "Rupee.h"
#include "Heart.h"

DeathCloud::DeathCloud(Entity* a_owner, float a_fX, float a_fY)
	: Entity("blank", a_fX, a_fY)
{
	m_type = EFFECT;
	m_pSprite->LoadSpritesheet("deathCloud", 24, 24, 3, 1);
	m_pSprite->AddAnimation("poof", Vector2i(0,0), Vector2i(2,0));
	m_pSprite->PlayAnimation("poof", false);
	m_owner = a_owner;

	m_pSprite->m_fAnimationSpeed = 2;

	m_collisionRect = CollisionRectangle(0, 20, 0, 16);
	m_bCollidesWithTiles = false;
}


DeathCloud::~DeathCloud(void)
{
}


void DeathCloud::Update(float a_fDeltaTime)
{
	Entity::Update(a_fDeltaTime);
	m_position = m_owner->GetPosition() - Vector2(3, -6);
	if(m_pSprite->m_sCurrentAnimation == "idle")
	{
		if(rand()%50 > 42)
		{
			new Heart(m_position.x + 8, m_position.y + 8);
		}
		else
		{
			new Rupee(m_position.x + 8, m_position.y + 8);
		}
		m_state = REMOVED;
		m_owner->m_state = REMOVED;
	}
}