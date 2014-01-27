// Template, major revision 3
// IGAD/NHTV - Jacco Bikker - 2006-2009
#include "GamePlayingState.h"
#include "GameMenuState.h"
#include "EntityManager.h"
#include "TileManager.h"
#include "Stats.h"

using namespace Tmpl8;

Game::~Game()
{	
	delete player;
}

void Game::Init()
{
	srand(time(NULL));
	SetState(GameMenuState::getInstance());
	
	m_pWorld = new World();
	m_pWorld->Init();
	
	Tiles->m_pWorld = m_pWorld;
	m_fUpdateTimer = 0;
}

void Game::Tick( float a_fDeltaTime )
{
	Update(a_fDeltaTime);
	Draw();
}

void Game::Update(float a_fDeltaTime)
{
	m_pWorld->Update(a_fDeltaTime);
	m_pCurrentState->Update(this, a_fDeltaTime);
}

void Game::Draw()
{
	m_Screen->Clear(0);

	m_pWorld->Draw(m_Screen);

	m_pCurrentState->Draw(this, m_Screen);	
}


void Game::SetState(State<Game>* a_state)
{
	m_pCurrentState = a_state;
	a_state->Enter(this);
}


State<Game>* Game::GetState()
{
	return m_pCurrentState;
}


void Game::ChangeState(State<Game>* a_newState)
{
	m_pCurrentState->Exit(this);

	m_pCurrentState = a_newState;
	m_pCurrentState->Enter(this);
}