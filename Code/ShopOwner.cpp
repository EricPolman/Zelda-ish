#include "ShopOwner.h"
#include "UserInterface.h"

ShopOwner::ShopOwner(float a_fX, float a_fY, Player* a_pPlayer, Room* a_room)
	: Entity("blank", a_fX, a_fY, a_room)
{
	m_pSprite->LoadSpritesheet("shopowner", 16, 25, 1, 1);
	m_pPlayer = a_pPlayer;
	m_collisionRect = CollisionRectangle(0, 0, m_pSprite->GetWidth(), m_pSprite->GetHeight());
	m_bCollidesWithTiles = false;
	m_bIsVicky = false;
}


ShopOwner::~ShopOwner(void)
{
}


void ShopOwner::Update(float a_fDeltaTime)
{
	Entity::Update(a_fDeltaTime);
	
	if(!m_pPlayer->HasWeapons())
	{
		if(m_pPlayer->GetRupees() < 1000)
		{
			UserInterface::DrawText("COME BACK WHEN YOU HAVE THE MONEY.", 144, m_position.y - 140);
			UserInterface::DrawText("I HEARD THE SOLDIERS STASH THEIR LOOT", 144, m_position.y - 120);
			UserInterface::DrawText("IN THE CAVE AT THE SMITHS HOUSE TO ", 144, m_position.y - 110);
			UserInterface::DrawText("THE EAST OF THE VILLAGE. ", 144, m_position.y - 100);
			UserInterface::DrawText("THOSE CHESTS SHOULD BREAK OPEN WITH Q. ", 144, m_position.y - 90);
			
			UserInterface::DrawText("ONLY A FOOL WOULD TRY TO STEAL THAT", 144, m_position.y - 70);
			UserInterface::DrawText("SO... BEAT IT AND COME BACK IF YOU", 144, m_position.y - 60);
			UserInterface::DrawText("CAN AFFORD THESE FINE GOODS.", 144, m_position.y - 50);
		}
		else
		{
			UserInterface::DrawText("THEY WILL HAVE YOUR HEAD FOR STEALING", 144, m_position.y - 70);
			UserInterface::DrawText("THAT. NOT MY PROBLEM THOUGH. PRESS Q", 144, m_position.y - 60);
			UserInterface::DrawText("NEAR THE WEAPONS TO BUY THEM.", 144, m_position.y - 50);
		}
	}
	else
	{
		if(!m_bIsVicky)
		{
			UserInterface::DrawText("I SUGGEST YOU GET OUT OF THE VILLAGE,", 144, m_position.y - 70);
			UserInterface::DrawText("THEY DONT LIKE THIEVES AROUND HERE.", 144, m_position.y - 60);
			UserInterface::DrawText("THE SOUTH SHOULD OFFER YOU A NEW ADVENTURE.", 144, m_position.y - 50);
			if(Input->IsKeyPressed(SDLK_v))
			{
				m_bIsVicky = true;
			}
		}
		else
		{
			UserInterface::DrawText("YEAH, BUT NO, BUT YEAH, BUT NO, BUT YEAH,", 144, m_position.y - 160);
			UserInterface::DrawText("BUT NO BUT YEAH BUT, OH MY", 144, m_position.y - 150);
			UserInterface::DrawText("GOD THAT IS SO UNFAIR!", 144, m_position.y - 140);
			UserInterface::DrawText("EVERYBODY KNOWS I GAVE UP", 144, m_position.y - 130);
			UserInterface::DrawText("SMOKING WHEN I WAS LIKE, 9!", 144, m_position.y - 120);
			UserInterface::DrawText("ANYWAY IF ANYBODY'S BEEN BREAKING", 144, m_position.y - 110);
			UserInterface::DrawText("THE RULES IS HARMONY BUTLER,", 144, m_position.y - 100);
			UserInterface::DrawText("BECAUSE SHE STOLE SHANITA'S EYELINER", 144, m_position.y - 90);
			UserInterface::DrawText("PENCIL, AND DREW A PICTURE ON THE", 144, m_position.y - 80);
			UserInterface::DrawText("DORMITORY WALL OF A BIG FAT WOMAN", 144, m_position.y - 70);
			UserInterface::DrawText("WITH A PENIS AND WROTE YOUR NAME ON IT.", 144, m_position.y - 60);
			UserInterface::DrawText("I'M NOT SAYING YOU'RE A BIG FAT WOMAN", 144, m_position.y - 50);
			UserInterface::DrawText("WITH A PENIS, I'M JUST SAYING WHAT SHE DID!", 144, m_position.y - 40);
			if(Input->IsKeyPressed(SDLK_v))
			{
				m_bIsVicky = false;
			}
		}
	}
}