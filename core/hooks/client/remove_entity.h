#pragma once

class RemoveEntity {
public:
	typedef void(__fastcall* fnRemoveEntity)(EntitySystem*, C_BaseEntity*, C_BaseHandle);
	static inline fnRemoveEntity oRemoveEntity = nullptr;
	static void hkRemoveEntity(EntitySystem* entitySystem, C_BaseEntity* baseEntity, C_BaseHandle handle);
};