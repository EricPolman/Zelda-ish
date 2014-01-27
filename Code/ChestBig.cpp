#include "ChestBig.h"
#include "TriggerManager.h"
#include "TriggerChest.h"
#include "TextureManager.h"
#include "UserInterface.h"

ChestBig::ChestBig(float a_fX, float a_fY, Room* a_room)
	: Entity("blank", a_fX, a_fY, a_room)
{
	m_type = STATIC;
	m_pSprite->LoadSpritesheet("chest_big", 32, 24, 2, 1);
	m_pSprite->AddAnimation("closed", Vector2i(0,0), Vector2i(0,0));
	m_pSprite->AddAnimation("opened", Vector2i(1,0), Vector2i(1,0));
	m_collisionRect = CollisionRectangle(0,0, m_pSprite->GetWidth(), m_pSprite->GetHeight());
	m_bCollidesWithTiles = false;

	m_bIsOpened = false;
	m_bRewardShown = false;
	m_fShowRewardTimer = 0;

	TriggerChest* tC = new TriggerChest(m_position.x + 16, m_position.y + 26);
	Triggers->Add(tC, a_room);
	tC->m_pChestBig = this;

	m_pContents = Textures->m_Textures["boomerang_unlock"];
}


ChestBig::~ChestBig(void)
{
}


void ChestBig::Update(float a_fDeltaTime)
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


void ChestBig::Hit(Entity* a_pOther, CollisionInfo a_info)
{
	
}


void ChestBig::Draw(Tmpl8::Surface* a_screen, Vector2 a_origin)
{
	Entity::Draw(a_screen, a_origin);
	if(m_bIsOpened)
	{
		UserInterface::DrawText("CONGRATULATIONS!", m_position.x - 60, m_position.y - 35);
		UserInterface::DrawText("YOU HAVE A BOOMERANG NOW.", m_position.x - 60, m_position.y - 25);
		UserInterface::DrawText("PRESS E TO USE IT.", m_position.x - 60, m_position.y - 15);

		if(!m_bRewardShown)
			m_pContents->CopyTo(a_screen, m_position.x + 11, m_position.y - 4 - m_fShowRewardTimer * 16, true);
	}
}


void ChestBig::Open(Entity* a_pPlayer)
{
	if(!m_bIsOpened)
	{
		m_bIsOpened = true;
		m_pSprite->PlayAnimation("opened", true);
		Player* player = (Player*)a_pPlayer;
		player->EnableBoomerang();
	}
}