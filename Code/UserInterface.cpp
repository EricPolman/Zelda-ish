#include "UserInterface.h"
#include "TextureManager.h"

Tmpl8::Surface* UserInterface::m_pHeartHalf;
Tmpl8::Surface* UserInterface::m_pHeartFull;
Tmpl8::Surface* UserInterface::m_pRupee;
Player* UserInterface::m_pPlayer;
std::queue<UIText> UserInterface::m_uiTexts;

UserInterface::UserInterface(void)
{
	Player* m_pPlayer = 0;
	
	Textures->Add("heart_half", "assets/sprites/heart_half.png");
	Textures->Add("heart_full", "assets/sprites/heart_full.png");
	Textures->Add("rupee_ui", "assets/sprites/rupee_ui.png");
	m_pHeartHalf = Textures->m_Textures["heart_half"];
	m_pHeartFull = Textures->m_Textures["heart_full"];
	m_pRupee = Textures->m_Textures["rupee_ui"];
}


UserInterface::~UserInterface(void)
{
}


void UserInterface::Update(float a_fDeltaTime)
{

}

std::ostringstream sstreamRupees;
void UserInterface::Draw(Tmpl8::Surface* a_screen)
{
	int fullLives = m_pPlayer->GetHealth() / 2;
	int halfLives = m_pPlayer->GetHealth() % 2;
	a_screen->Print("LIVES", a_screen->GetWidth() - 112, 12, 0xFFFFFFFF);

	for(int i = 0; i < fullLives; i++)
	{
		m_pHeartFull->CopyTo(a_screen, a_screen->GetWidth() - 128 + (i * 18), 20, true);
	}
	if(halfLives != 0)
	{
		m_pHeartHalf->CopyTo(a_screen, a_screen->GetWidth() - 128 + (fullLives * 18), 20, true);
	}
	
	m_pRupee->CopyTo(a_screen, 25, 12, true);
	sstreamRupees << m_pPlayer->GetRupees();
	a_screen->Print(sstreamRupees.str().c_str(), 35, 13, 0xFFFFFFFF);
	sstreamRupees.str("");

	while(m_uiTexts.size() > 0)
	{
		UIText uiText = m_uiTexts.front();
		a_screen->Print(uiText.str, uiText.x, uiText.y, 0xFFFFFFFF);
		m_uiTexts.pop();
	}
}


void UserInterface::DrawText(const char* a_string, int a_x, int a_y)
{
	UIText uiText;
	uiText.str = a_string;
	uiText.x = a_x;
	uiText.y = a_y;
	m_uiTexts.push(uiText);
}