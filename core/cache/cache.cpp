#include "cache.h"

void Cache::PushToCache(C_BaseEntity* pEntity, C_BaseHandle baseHandle, CCSPlayerController* pController, int entityIndex)
{
	std::unique_lock lock(sharedMutex);

	EntityMap[pEntity] = { pEntity,baseHandle,pController,entityIndex };
}

void Cache::RemoveFromCache(C_BaseEntity* pEntity)
{
	std::unique_lock lock(sharedMutex);
	EntityMap.erase(pEntity);
}

void Cache::Cleanup()
{
	std::unique_lock lock(sharedMutex);
	EntityMap.clear();
}

std::vector<Cache::Entities> Cache::GetEntitiesFromCache()
{
	std::shared_lock lock(sharedMutex);
	std::vector<Entities> entities;
	entities.reserve(EntityMap.size());
	for (auto& [key, info] : EntityMap)
		entities.push_back(info);
	return entities;
}
