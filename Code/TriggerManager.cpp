#include "TriggerManager.h"

TriggerManager::~TriggerManager(void)
{
	instanceFlag = false;
	for(std::map<Room*, std::vector<Trigger*>>::iterator iter = m_triggersOfRoom.begin(); iter != m_triggersOfRoom.end(); iter++)
	{
		for(std::vector<Trigger*>::iterator i = iter->second.begin(); i != iter->second.end(); ++i )
		{
			delete *i;
		}
		iter->second.clear();
	}
}

bool TriggerManager::instanceFlag = false;
TriggerManager* TriggerManager::single = NULL;
TriggerManager* TriggerManager::GetInstance()
{
    if(! instanceFlag)
    {
        single = new TriggerManager();
		single->m_player = 0;
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}


void TriggerManager::Update(float a_fDeltaTime)
{
	for(std::vector<Trigger*>::iterator iter = m_triggersOfRoom[m_pCurrentRoom].begin(); iter != m_triggersOfRoom[m_pCurrentRoom].end(); iter++)
	{
		if(!(*iter)->Update(a_fDeltaTime, m_player))
		{
			break;
		}
	}
}


void TriggerManager::Add(Trigger* a_pTrigger)
{
	GetTriggers(m_pCurrentRoom)->push_back(a_pTrigger);
}


void TriggerManager::Add(Trigger* a_pTrigger, Room* a_room)
{
	GetTriggers(a_room)->push_back(a_pTrigger);
}


std::vector<Trigger*>* TriggerManager::GetTriggers(Room* a_room)
{
	return &m_triggersOfRoom[a_room];
}