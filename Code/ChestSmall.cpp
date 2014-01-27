#include "ChestSmall.h"
#include "TriggerManager.h"
#include "TriggerChest.h"
#include "TextureManager.h"

ChestSmall::ChestSmall(float a_fX, float a_fY, Room* a_room)
	: Entity("shrub", a_fX, a_fY, a_room)
{
	m_type = STATIC;
	m_pSprite->LoadSpritesheet("chest_small", 16, 16, 2, 1);
	m_pSprite->AddAnimation("closed", Vector2i(0,0), Vector2i(0,0));
	m_pSprite->AddAnimation("opened", Vector2i(1,0), Vector2i(1,0));
	m_collisionRect = CollisionRectangle(0,0, m_pSprite->GetWidth(), m_pSprite->GetHeight());
	m_bCollidesWithTiles = false;

	m_bIsOpened = false;
	m_bRewardShown = false;
	m_fShowRewardTimer = 0;

	TriggerChest* tC = new TriggerChest(m_position.x + 8, m_position.y + 18);
	Triggers->Add(tC, a_room);
	tC->m_pChest = this;

	m_pContents = Textures->m_Textures["rupee_red_chest"];
}


ChestSmall::~ChestSmall(void)
{
}


void ChestSmall::Update(float a_fDeltaTime)
{
	if(m_bIsOpened && !m_bRewardShown)
	{
		m_fShowRewardTimer += a_fDeltaTime;
		if(m_fShowRewardTimer > 0.5f)
		{
			m_bRewardShown = true;
		}
	}
}


void ChestSmall::Hit(Entity* a_pOther, CollisionInfo a_info)
{
	
}


void ChestSmall::Draw(Tmpl8::Surface* a_screen, Vector2 a_origin)
{
	Entity::Draw(a_screen, a_origin);
	if(m_bIsOpened && !m_bRewardShown)
	{
		m_pContents->CopyTo(a_screen, m_position.x + 1, m_position.y - 4 - m_fShowRewardTimer * 12, true);
	}
}


void ChestSmall::Open(Entity* a_pPlayer)
{
	if(!m_bIsOpened)
	{
		m_bIsOpened = true;
		m_pSprite->PlayAnimation("opened", true);
		Player* player = (Player*)a_pPlayer;
		player->AddRupees(500);
	}
}