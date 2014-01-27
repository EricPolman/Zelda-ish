#pragma once
#include "includes.h"
#include "AnimatedSprite.h"
#include "Room.h"

enum EntityType{ENTITY,PLAYER,ENEMY, SWORD_SLASH, DESTROYABLE, EFFECT, PLAYER_WEAPON, STATIC, PICKUP, BOSS};
enum EntityState{ALIVE, DEAD, REMOVED};

class Entity
{
public:
	Entity(std::string a_tilesheetName, float a_fX = 0, float a_fY = 0, Room* a_room = 0); 
	virtual ~Entity(void);
	
	EntityState m_state;
	EntityType m_type;

	virtual void Update(float a_fDeltaTime);
	virtual void Draw(Tmpl8::Surface* a_screen, Vector2 a_origin);
	virtual void Hit(Entity* a_pOther, CollisionInfo a_info);
	virtual void Move(Vector2 a_translation);
	virtual void Move(float a_fX, float a_fY);
	
	void SetPosition(Vector2 a_position){m_position = a_position;}
	inline Vector2 GetPosition(){return m_position;}
	
	void SetSprite(AnimatedSprite* a_pSprite){m_pSprite = a_pSprite;}
	inline AnimatedSprite* GetSprite(){return m_pSprite;}
	
	Vector2 m_velocity;

	bool m_bIsVisible;
	CollisionRectangle m_collisionRect;
	bool m_bCollidesWithTiles;
protected:
	Vector2 m_position;
	AnimatedSprite* m_pSprite;
};

