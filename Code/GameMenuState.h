#pragma once
#include "state.h"
#include "game.h"

using namespace Tmpl8;

class GameMenuState :
	public State<Game>
{
private:
	GameMenuState(void);
	
    static bool instanceFlag;
    static GameMenuState *single;
public:
	~GameMenuState(void);
    static GameMenuState* getInstance();

	void Enter(Game* a_game);
	void Update(Game* a_game, float a_fDeltaTime);
	void Draw(Game* a_game, Tmpl8::Surface* a_screen);
	void Hit(Game* a_game, Entity* a_pOther){};
	void Exit(Game* a_game){};
};

