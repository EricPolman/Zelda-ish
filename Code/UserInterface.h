#pragma once
#include "includes.h"
#include "Player.h"

struct UIText{int x; int y; const char* str;};

class UserInterface
{
public:
	UserInterface(void);
	~UserInterface(void);
	
	static void Update(float a_fDeltaTime);
	static void Draw(Tmpl8::Surface* a_screen);
	static void DrawText(const char* a_string, int a_x, int a_y);
	static std::queue<UIText> m_uiTexts;

	static void SetPlayer(Player* a_pPlayer){m_pPlayer = a_pPlayer;}
	static Tmpl8::Surface* m_pHeartHalf;
	static Tmpl8::Surface* m_pHeartFull;
	static Tmpl8::Surface* m_pRupee;
	static Player* m_pPlayer;
};

