#include "Entity.h"
#include "EntityManager.h"


Entity::Entity(std::string a_tilesheetName,float a_fX, float a_fY, Room* a_room)
{
	m_pSprite = new AnimatedSprite();
	m_pSprite->LoadSpritesheet(a_tilesheetName, 24, 24, 1, 1);

	m_position.x = a_fX;
	m_position.y = a_fY;
	m_state = ALIVE;
	m_type = ENTITY;
	m_bIsVisible = true;
	m_bCollidesWithTiles = true;
	m_collisionRect = CollisionRectangle(0,0, m_pSprite->GetWidth(), m_pSprite->GetHeight());
	if(a_room != 0)
	{
		Entities->Add(this, a_room);
	}
	else
	{
		Entities->Add(this);
	}
}


Entity::~Entity(void)
{
	Entities->Remove(this);
}


void Entity::Update(float a_fDeltaTime)
{
	m_pSprite->Update(a_fDeltaTime);
}


void Entity::Hit(Entity* a_pOther, CollisionInfo a_info)
{

}


void Entity::Draw(Tmpl8::Surface* a_surface, Vector2 a_origin)
{
	if(m_bIsVisible)
	{
		m_pSprite->Draw(a_surface, a_origin + m_position);//CopyTo(a_surface, a_origin.x + m_position.x, a_origin.y + m_position.y, true);
	}
}


void Entity::Move(float a_fX, float a_fY)
{
	m_position.x += a_fX;
	m_position.y += a_fY;
}


void Entity::Move(Vector2 a_translation)
{
	m_position.x += a_translation.x;
	m_position.y += a_translation.y;
}
