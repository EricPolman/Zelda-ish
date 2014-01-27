#pragma once
#include "includes.h"
#include "Entity.h"

template <class entity_type>
class State
{
public:
	virtual ~State(){}

	virtual void Enter(entity_type*)=0;
	virtual void Update(entity_type* a_entity, float a_fDeltaTime)=0;
	virtual void Draw(entity_type* a_entity, Tmpl8::Surface* a_screen)=0;
	virtual void Hit(entity_type* a_entity, Entity* a_otherEntity)=0;
	virtual void Exit(entity_type*)=0;
};
