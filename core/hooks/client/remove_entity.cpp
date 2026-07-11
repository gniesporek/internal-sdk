#include "../hooks.h"

void RemoveEntity::hkRemoveEntity(EntitySystem* entitySystem, C_BaseEntity* baseEntity, C_BaseHandle handle)
{
	Cache::RemoveFromCache(baseEntity);

	MESSAGE_INFO("removed entity %s with index %d", baseEntity->GetSchemaClassBinding()->szName, entitySystem->GetEntityIndex(baseEntity));

	oRemoveEntity(entitySystem, baseEntity, handle);
}
