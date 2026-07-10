#include "entity_system.h"

C_BaseEntity* EntitySystem::GetEntityByIndex(int index)
{
	// "'%s' : '%s' (entindex %d) \n", "Found no entity at %d.\n", "Format: ent_find_index <index>\n"
	typedef C_BaseEntity* (__fastcall* fnGetBaseEntity)(EntitySystem*, int);
	static auto fnGetEntity = (fnGetBaseEntity)(Utils::Memory::RelativeAddress(Utils::Memory::SignatureScan("client.dll", "E9 ? ? ? ? CC CC 48 8B 89"), 1, 5));
	return fnGetEntity(EntitySystem::pEntitySystem, index);
}

C_BaseEntity* EntitySystem::GetEntityByHandle(C_BaseHandle handle)
{
	if (!handle.IsValid())
		return nullptr;

	C_BaseEntity* entity = GetEntityByIndex(handle.GetEntryIndex());

	if (!entity)
		return nullptr;

	return entity;
}

C_BaseEntity* EntitySystem::CreateEntityByName(const char* szName)
{
	// "Attempted to create unknown entity classname \"%s\"!\n"
	typedef C_BaseEntity* (__fastcall* fnCreateEntityByName)(EntitySystem* a1, int a2, const char* a3, int a4, int a5, int a6, char a7);
	static fnCreateEntityByName CreateEntity = (fnCreateEntityByName)(Utils::Memory::RelativeAddress(Utils::Memory::SignatureScan("client.dll", "E8 ? ? ? ? 48 8B D8 48 85 C0 75 ? 33 C0 EB ? 48 8B 48"), 1, 5));
	return CreateEntity(EntitySystem::pEntitySystem, -1, szName, 0, -1, -1, 0);
}

int EntitySystem::GetHighestEntityIndex()
{
	int highestIndex = -1;

	for (int block = 31; block >= 0; --block)
	{
		uintptr_t pointerToEnts = *(uintptr_t*)((uintptr_t)EntitySystem::pEntitySystem + 0x10 + (static_cast<unsigned long long>(block) * 0x8));
		if (!pointerToEnts)
			continue;

		for (int i = 511; i >= 0; --i)
		{
			if (*(uintptr_t*)(pointerToEnts + 0x70 * static_cast<unsigned long long>(i)))
			{
				highestIndex = (block * 512) + i;
				return highestIndex;
			}
		}
	}

	return highestIndex;
}

int EntitySystem::GetEntityIndex(C_BaseEntity* entity)
{
	/*
	> cl_showents
	[Console] Ent     0: class CWorld name ""
	[Console] Ent     1: class CCSPlayerController name ""
	[Console] Ent     2: class CCSPlayerController name ""
	[Console] Ent     3: class CCSPlayerController name ""
	[Console] Ent     4: class CCSPlayerController name ""
[	Console] Ent     5: class CCSPlayerController name ""
	*/

	int index = -1;

	typedef int(__fastcall* fnGetEntityIndex)(void*, int&);
	static fnGetEntityIndex GetEntityIndexFn = (fnGetEntityIndex)(Utils::Memory::RelativeAddress(Utils::Memory::SignatureScan("client.dll", "E8 ? ? ? ? 8B 45 ? 44 8D 68"), 1, 5));

	if (!GetEntityIndexFn)
		return -1;

	GetEntityIndexFn(entity, index);

	return index;
}
