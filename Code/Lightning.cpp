#include "Lightning.h"
#include "Player.h"

Lightning::Lightning(float a_fX, float a_fY, Room* a_room)
	: Entity("blank", a_fX, a_fY, a_room)
{
	m_type = EntityType::BOSS;
	m_pSprite->LoadSpritesheet("lightning", 415/5, 150, 5, 1);
	m_pSprite->AddAnimation("spark", Vector2i(0,0), Vector2i(4,0));
	m_pSprite->PlayAnimation("spark", false);
	m_collisionRect = CollisionRectangle(0,0, m_pSprite->GetWidth(), m_pSprite->GetHeight());
	m_bCollidesWithTiles = false;
}


Lightning::~Lightning(void)
{
}


void Lightning::Hit(Entity* a_pOther, CollisionInfo a_info)
{
	if(a_pOther->m_type == PLAYER)
	{
		((Player*)a_pOther)->DecreaseHealth(1);
	}
}


void Lightning::Update(float a_fDeltaTime)
{
	Entity::Update(a_fDeltaTime);
	if(m_pSprite->m_sCurrentAnimation == "idle")
	{
		m_state = REMOVED;
		m_bIsVisible = false;
	}
}