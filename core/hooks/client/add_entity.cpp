#include "../hooks.h"

void AddEntity::hkAddEntity(EntitySystem* entitySystem, C_BaseEntity* baseEntity, C_BaseHandle handle)
{
	oAddEntity(entitySystem, baseEntity, handle);

	static CCSPlayerController* pController = nullptr;

	if (baseEntity->IsEntityPlayerController()) {
		pController = (CCSPlayerController*)baseEntity;
	}

	MESSAGE_INFO("added entity with index %d", EntitySystem::GetEntityIndex(baseEntity));

	Cache::PushToCache(baseEntity, handle, pController, EntitySystem::GetEntityIndex(baseEntity));
}
