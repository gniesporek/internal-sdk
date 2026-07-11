#include "../hooks.h"

// add more entities to our cache

void AddEntity::hkAddEntity(EntitySystem* entitySystem, C_BaseEntity* baseEntity, C_BaseHandle handle)
{
	oAddEntity(entitySystem, baseEntity, handle);

	static CCSPlayerController* pController = nullptr;

	if (baseEntity->IsEntityPlayerController()) {
		pController = (CCSPlayerController*)baseEntity;
	}

	MESSAGE_INFO("added entity %s with index %d", baseEntity->GetSchemaClassBinding()->szName, entitySystem->GetEntityIndex(baseEntity));

	Cache::PushToCache(baseEntity, handle, pController, entitySystem->GetEntityIndex(baseEntity));
}
