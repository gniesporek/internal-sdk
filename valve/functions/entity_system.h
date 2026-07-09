#pragma once

#include "../../core/utils/utils.h"

#include "../classes/classes.h"

class EntitySystem 
{
public:
	static bool Setup();
	static C_BaseEntity* GetEntityByIndex(int index);
	static C_BaseEntity* GetEntityByHandle(C_BaseHandle handle);
private:
	static inline EntitySystem* pEntitySystem;
};