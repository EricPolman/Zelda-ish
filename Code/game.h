// Template, major revision 3, beta
// IGAD/NHTV - Jacco Bikker - 2006-2009

#pragma once
#include "includes.h"
#include "State.h"
#include "Player.h"
#include "World.h"

namespace Tmpl8 {
	class Game
	{ 
	public:
		void SetTarget( Surface* a_Surface ) { m_Screen = a_Surface; }
		~Game();
		Player* player;

		void Init();
		void Tick( float a_fDeltaTime );
		void MouseMove( unsigned int x, unsigned int y ) {}
		void MouseUp( unsigned int button ) {}
		void MouseDown( unsigned int button ) {}
		
		void ChangeState(State<Game>* a_newState);
		void SetState(State<Game>* a_state);
		State<Game>* GetState();

		void Update(float a_fDeltaTime);
		void Draw();

		Surface* m_Screen;
		World* m_pWorld;
	private:
		float m_fUpdateTimer;
		State<Game>* m_pCurrentState;
	};
}; // namespace Tmpl8