#pragma once
#include "Entity.h"
#include "World.h"
#include "Room.h"

class EntityManager
{
public:
	~EntityManager(void);
	static EntityManager* GetInstance(void);

	void Update(float a_fDeltaTime, Room* a_room);
	void Draw(Tmpl8::Surface* a_screen, Vector2 a_origin, Room* a_room);
	void Remove(Entity* a_pEntity);
	void Add(Entity* a_pEntity);
	void Add(Entity* a_pEntity, Room* a_room);
	std::vector<Entity*>* GetEntities(Room* a_room);
	std::queue<Entity*>* GetEntityQueue(Room* a_room){return &m_entityQueue[a_room];}
	void PushQueues();
	void ClearAll();
	Entity* m_pCameraCenter;
	
	void AddEntityVectorForRoom(Room* a_room)
	{
		std::map<Room*, std::vector<Entity*>>::iterator i = m_entitiesOfRoom.find(a_room);
		if (i == m_entitiesOfRoom.end()) { 
			m_entitiesOfRoom[a_room] = std::vector<Entity*>();
		}
		std::map<Room*, std::queue<Entity*>>::iterator j = m_entityQueue.find(a_room);
		if (j == m_entityQueue.end()) { 
			m_entityQueue[a_room] = std::queue<Entity*>(); 
		}
	}

	void SetCurrentRoom(Room* a_room){m_pCurrentRoom = a_room;}
	void SetPlayer(Entity* a_pPlayer);
private:
	std::vector<Entity*> m_toBeRemoved;
	static bool instanceFlag;

	//std::vector<Entity*> m_entities;
	std::map<Room*, std::vector<Entity*>> m_entitiesOfRoom;
	std::map<Room*, std::queue<Entity*>> m_entityQueue;

	static EntityManager *single;
	EntityManager(void){}

	struct EntityIsAboveOther
	{
		bool operator()( Entity* entity1, Entity* entity2 ) const {
			return entity1->GetPosition().y + entity1->m_collisionRect.y + entity1->m_collisionRect.height < entity2->GetPosition().y + entity2->m_collisionRect.y + entity2->m_collisionRect.height;
		}
	};

	Room* m_pCurrentRoom;
};


#define Entities EntityManager::GetInstance()