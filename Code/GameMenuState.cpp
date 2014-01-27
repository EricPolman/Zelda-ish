#include "GameMenuState.h"
#include "EntityManager.h"

bool GameMenuState::instanceFlag = false;

GameMenuState* GameMenuState::single = NULL;
GameMenuState* GameMenuState::getInstance()
{
    if(!instanceFlag)
    {
        single = new GameMenuState();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}

GameMenuState::~GameMenuState()
{
	instanceFlag = false;
}


GameMenuState::GameMenuState(void)
{	
	
}


void GameMenuState::Enter(Game* a_game)
{
	
}


void GameMenuState::Update(Game* a_game, float a_fDeltaTime)
{
	
}


void GameMenuState::Draw(Game* a_game, Tmpl8::Surface* a_screen)
{
	
}