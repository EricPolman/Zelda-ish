#include "GamePlayingState.h"
#include "EntityManager.h"

bool GamePlayingState::instanceFlag = false;

GamePlayingState* GamePlayingState::single = NULL;
GamePlayingState* GamePlayingState::getInstance()
{
    if(!instanceFlag)
    {
        single = new GamePlayingState();
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}

GamePlayingState::~GamePlayingState()
{
	instanceFlag = false;
}


GamePlayingState::GamePlayingState(void)
{	
	
}


void GamePlayingState::Enter(Game* a_game)
{
	
}


void GamePlayingState::Update(Game* a_game, float a_fDeltaTime)
{
	
}


void GamePlayingState::Draw(Game* a_game, Tmpl8::Surface* a_screen)
{
	
}


void GamePlayingState::Exit(Game* a_game)
{
	ClearEntities();
	delete a_game->player;
}


void GamePlayingState::ClearEntities()
{
	Entities->ClearAll();
}