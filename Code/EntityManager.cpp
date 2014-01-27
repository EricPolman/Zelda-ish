#include "EntityManager.h"
#include "TileManager.h"

EntityManager::~EntityManager(void)
{
	instanceFlag = false;
	for(std::map<Room*, std::vector<Entity*>>::iterator iter = m_entitiesOfRoom.begin(); iter != m_entitiesOfRoom.end(); iter++)
	{
		for(std::vector<Entity*>::iterator i = iter->second.begin(); i != iter->second.end(); ++i )
		{
			delete *i;
		}
		iter->second.clear();
	}
	for(std::vector<Entity*>::iterator i = m_toBeRemoved.begin(); i != m_toBeRemoved.end(); ++i )
	{
		delete *i;
	}
	m_toBeRemoved.clear();
}

bool EntityManager::instanceFlag = false;
EntityManager* EntityManager::single = NULL;
EntityManager* EntityManager::GetInstance()
{
    if(! instanceFlag)
    {
        single = new EntityManager();
		single->m_pCameraCenter = 0;
        instanceFlag = true;
        return single;
    }
    else
    {
        return single;
    }
}


void EntityManager::Add(Entity* a_pEntity)
{
	m_entityQueue[m_pCurrentRoom].push(a_pEntity);
	//GetEntities(m_pCurrentRoom)->push_back(a_pEntity);
}


void EntityManager::Add(Entity* a_pEntity, Room* a_room)
{
	m_entityQueue[a_room].push(a_pEntity);
	//GetEntities(m_pCurrentRoom)->push_back(a_pEntity);
}


void EntityManager::Remove(Entity* a_pEntity)
{
	for(std::vector<Entity*>::iterator i = GetEntities(m_pCurrentRoom)->begin(); i != GetEntities(m_pCurrentRoom)->end(); i++)
	{
		if(*i == a_pEntity)
		{
			GetEntities(m_pCurrentRoom)->erase(i);
			break;
		}
	}
}

void EntityManager::ClearAll()
{
	for(std::map<Room*, std::vector<Entity*>>::iterator iter = m_entitiesOfRoom.begin(); iter != m_entitiesOfRoom.end(); iter++)
	{
		for(std::vector<Entity*>::iterator i = iter->second.begin(); i != iter->second.end(); ++i )
		{
			delete *i;
		}
		iter->second.clear();
	}
}


void EntityManager::Update(float a_fDeltaTime, Room* a_room)
{
	while(!m_entityQueue[a_room].empty())
	{
		GetEntities(a_room)->push_back(m_entityQueue[a_room].front());
		m_entityQueue[a_room].pop();
	}

	std::sort(GetEntities(a_room)->begin(), GetEntities(a_room)->end(), EntityIsAboveOther());

	for(std::vector<Entity*>::iterator i = GetEntities(a_room)->begin(); i != GetEntities(a_room)->end();)
	{
		Entity* iEntity = *i;

		if(iEntity->m_state == EntityState::REMOVED)
		{
			m_toBeRemoved.push_back(*i);
			i = GetEntities(a_room)->erase(i);
			continue;
		}
		else
		{
			i++;
		}

		iEntity->Update(a_fDeltaTime);
	}

	if(m_toBeRemoved.size() > 0)
	{
		for(std::vector<Entity*>::iterator i = m_toBeRemoved.begin(); i != m_toBeRemoved.end(); ++i )
		{
			delete *i;
		}
		m_toBeRemoved.clear();
	}
}


void EntityManager::Draw(Tmpl8::Surface* a_surface, Vector2 a_origin, Room* a_room)
{
	for(std::vector<Entity*>::iterator i = GetEntities(a_room)->begin(); i != GetEntities(a_room)->end(); i++)
	{
		(*i)->Draw(a_surface, a_origin);
	}
}


std::vector<Entity*>* EntityManager::GetEntities(Room* a_room)
{
	return &m_entitiesOfRoom[a_room];
}

void EntityManager::SetPlayer(Entity* a_pPlayer)
{
	m_pCameraCenter = a_pPlayer;
	for(std::map<Room*, std::vector<Entity*>>::iterator iter = m_entitiesOfRoom.begin(); iter != m_entitiesOfRoom.end(); iter++)
	{
		if(iter->first == m_pCurrentRoom)
			continue;
		(*iter).second.push_back(a_pPlayer);
	}
}


void EntityManager::PushQueues()
{
	for(int roomX = 0; roomX < COLS_OF_ROOMS; roomX++)
	{
		for(int roomY = 0; roomY < ROWS_OF_ROOMS; roomY++)
		{
			Room * room = Tiles->GetRoom(roomY + roomX * ROWS_OF_ROOMS);
			while(!m_entityQueue[room].empty())
			{
				GetEntities(room)->push_back(m_entityQueue[room].front());
				m_entityQueue[room].pop();
			}
		}
	}
}