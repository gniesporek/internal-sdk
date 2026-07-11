#pragma once

#include "../utils/utils.h"

#include "../../valve/classes/classes.h"

#include "../../valve/functions/entity_system.h"

#include <unordered_map>
#include <shared_mutex>

class Cache
{
public:

	class Entities {
	public:
		C_BaseEntity* pBaseEntity = nullptr;
		C_BaseHandle BaseHandle;
		CCSPlayerController* pPlayerController;
		int EntityIndex = 0;
	};

	static void PushToCache(C_BaseEntity* pEntity, C_BaseHandle baseHandle, CCSPlayerController* pController, int entityIndex);
	static void RemoveFromCache(C_BaseEntity* pEntity);
	static void Cleanup();
	static std::vector<Entities> GetEntitiesFromCache();
private:
	static inline std::unordered_map<C_BaseEntity*, Entities> EntityMap;
	static inline std::shared_mutex sharedMutex;
};