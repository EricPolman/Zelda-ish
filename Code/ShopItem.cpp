#include "ShopItem.h"
#include "TriggerManager.h"
#include "TriggerShopItem.h"
#include "TextureManager.h"
#include "UserInterface.h"

ShopItem::ShopItem(Item a_item, int a_cost, float a_fX, float a_fY, Room* a_room)
	: Entity("blank", a_fX, a_fY, a_room)
{
	m_type = STATIC;
	m_bCollidesWithTiles = false;
	
	switch(a_item)
	{
	case ITEM_WEAPONS:
		m_pSprite->LoadSpritesheet("item_weapons", 16, 16, 1, 1);
		break;
	}

	m_item = a_item;
	
	m_collisionRect = CollisionRectangle(0,0, m_pSprite->GetWidth(), m_pSprite->GetHeight());
	
	m_iCost = a_cost;

	m_bIsBought = false;
	m_fShowRewardTimer = 0;

	TriggerShopItem* trigger = new TriggerShopItem(m_position.x + 8, m_position.y + 18);
	trigger->m_pItem = this;
	Triggers->Add(trigger, a_room);

	std::ostringstream priceStream;
	priceStream.str("");

	priceStream << m_iCost;
	m_sCostString = priceStream.str();
}


ShopItem::~ShopItem(void)
{
}


void ShopItem::Update(float a_fDeltaTime)
{
	
}


void ShopItem::Hit(Entity* a_pOther, CollisionInfo a_info)
{
	
}


void ShopItem::Draw(Tmpl8::Surface* a_screen, Vector2 a_origin)
{
	Entity::Draw(a_screen, a_origin);
	UserInterface::DrawText(m_sCostString.c_str(), m_position.x - 4, m_position.y - 7);
}


void ShopItem::Buy(Entity* a_pPlayer)
{
	if(!m_bIsBought)
	{
		Player* player = (Player*)a_pPlayer;
		if(player->GetRupees() < m_iCost)
			return;

		m_bIsBought = true;
		
		switch(m_item)
		{
		case ITEM_WEAPONS:
			((Player*)a_pPlayer)->EnableWeapons();
			break;
		}

		m_state = REMOVED;

		player->AddRupees(-m_iCost);
	}
}