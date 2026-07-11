#pragma once

class AddEntity {
public:

	typedef void(__fastcall* fnAddEntity)(EntitySystem*, C_BaseEntity*, C_BaseHandle);
	static inline fnAddEntity oAddEntity = nullptr;
	static void hkAddEntity(EntitySystem* entitySystem, C_BaseEntity* baseEntity, C_BaseHandle handle);
};