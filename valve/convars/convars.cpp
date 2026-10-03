#include "convars.h"

CConVar* IEngineCvar::FindVar(const char* convarName)
{
	uint64_t index = 0;
	IEngineCvar::GetFirstConvarIndex(index);

	while (index != 0xFFFFFFFFi64)
	{
		CConVar* convar = GetConvarByIndex(index);

		if (convar && strcmp(convar->szName, convarName) == 0)
			return convar;

		IEngineCvar::GetNextConvarIndex(index);
	}

	return nullptr;
}

CConVar* IEngineCvar::GetConVar(const char* name)
{
	auto it = IEngineCvar::ConvarMap.find(FNV1A::Hash(name));
	return it != IEngineCvar::ConvarMap.end() ? (CConVar*)it->second : nullptr;
}

void IEngineCvar::Setup()
{
	ConvarMap.clear();

	uint64_t index = 0;
	uint32_t count = 0;

	GetFirstConvarIndex(index);

	while ((uint16_t)index != 0xFFFF)
	{
		if (CConVar* convar = GetConvarByIndex(index))
		{
			if (convar->szName)
			{
				uint32_t hash = FNV1A::Hash(convar->szName);

				ConvarMap.emplace(hash, (uintptr_t)convar);
				count++;
			}
		}

		GetNextConvarIndex(index);
	}

	MESSAGE_SUCCESS("[+] dumped %d convars to map", count);
}

CConVar* IEngineCvar::GetConvarByIndex(uint64_t index)
{
	typedef CConVar* (__fastcall* GetConvarByIndexFn)(IEngineCvar*, uint64_t);
	static auto GetConvarByIndex = (GetConvarByIndexFn)(Utils::Memory::SignatureScan("tier0.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B DA 48 8D B9 ? ? ? ? 48 8B F1 FF 15 ? ? ? ? 8B D0 39 47 ? 75 ? 66 FF 47 ? EB ? 8B 07 90 85 C0 75 ? B9 ? ? ? ? F0 0F B1 0F 75 ? 66 C7 47 ? ? ? 89 57 ? EB ? 48 8B CF E8 ? ? ? ? BA"));
	return GetConvarByIndex(this, index);
}

void IEngineCvar::GetFirstConvarIndex(uint64_t& index)
{
	typedef void(__fastcall* GetFirstConvarIndexFn)(IEngineCvar*, uint64_t&);
	static auto GetFirstConvarIndex = (GetFirstConvarIndexFn)(Utils::Memory::SignatureScan("tier0.dll", "48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 48 8B F2 48 8D B9"));
	return GetFirstConvarIndex(this, index);
}

void IEngineCvar::GetNextConvarIndex(uint64_t& index)
{
	typedef uint64_t* (__fastcall* GetNextConvarIndexFn)(IEngineCvar*, uint64_t*, uint16_t);
	static auto GetNextConvarIndex = (GetNextConvarIndexFn)(Utils::Memory::SignatureScan("tier0.dll", "40 53 55 56 41 56 41 57 48 83 EC ? 49 8B D8 48 8D B1 ? ? ? ? 4C 8B F2 48 8B E9 FF 15 ? ? ? ? 8B D0 39 46 ? 75 ? 66 FF 46 ? EB ? 8B 06 90 85 C0 75 ? B9 ? ? ? ? F0 0F B1 0E 75 ? 66 C7 46 ? ? ? 89 56 ? EB ? 48 8B CE E8 ? ? ? ? 41 BF ? ? ? ? 48 89 7C 24 ? 4C 89 6C 24 ? 66 41 3B DF 74 ? 41 BD ? ? ? ? 66 44 85 6D"));
	GetNextConvarIndex(this, &index, index);
}