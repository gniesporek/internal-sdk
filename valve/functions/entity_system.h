#pragma once

#include "../../core/utils/utils.h"

#include "../classes/classes.h"

class EntitySystem 
{
public:
	static inline EntitySystem* pEntitySystem = nullptr; // global pointer to the entity system instance

	static C_BaseEntity* GetEntityByIndex(int index);
	static C_BaseEntity* GetEntityByHandle(C_BaseHandle handle);
	static C_BaseEntity* CreateEntityByName(const char* szName);
	static int GetHighestEntityIndex();
	static int GetEntityIndex(C_BaseEntity* entity);
};