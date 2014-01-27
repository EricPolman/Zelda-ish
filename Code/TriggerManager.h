#pragma once
#include "Trigger.h"

class TriggerManager
{
public:
	~TriggerManager(void);
	static TriggerManager* GetInstance(void);
	
	void Update(float a_fDeltaTime);

	void Add(Trigger* a_pTrigger);
	void Add(Trigger* a_pTrigger, Room* a_room);
	std::vector<Trigger*>* GetTriggers(Room* a_room);

	Room* m_pCurrentRoom;
	std::map<Room*, std::vector<Trigger*>> m_triggersOfRoom;
	Player* m_player;
private:
	static bool instanceFlag;

	static TriggerManager *single;
	TriggerManager(void){}
};


#define Triggers TriggerManager::GetInstance()