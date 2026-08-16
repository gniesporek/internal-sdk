#include "classes.h"

uint32_t CCSPlayerController::SetTickBase(uint32_t tickBase)
{
	return SchemaManager::GetOffset("CBasePlayerController", "m_nTickBase") ? *reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + SchemaManager::GetOffset("CBasePlayerController", "m_nTickBase")) = tickBase : 0;
}

CCSPlayerController* CCSPlayerController::GetLocalPlayer()
{
	// "GetLocalPlayerController" 
	typedef CCSPlayerController* (__fastcall* fnGetLocalPlayer)(int);
	static fnGetLocalPlayer GetLocalPlayerFn = (fnGetLocalPlayer)(Utils::Memory::SignatureScan("client.dll", "48 83 EC ? 83 F9 ? 75 ? 48 8B 0D ? ? ? ? 48 8D 54 24 ? 48 8B 01 FF 90 ? ? ? ? 8B 08 48 63 C1 48 8D 0D ? ? ? ? 48 8B 04 C1 48 83 C4 ? C3 CC CC CC CC CC CC CC CC CC CC CC CC CC 48 83 EC ? 83 F9"));
	return GetLocalPlayerFn(-1);
}

C_CSPlayerPawn* C_CSPlayerPawn::GetLocalPlayer()
{
	// "GetLocalPlayerPawn"
	typedef C_CSPlayerPawn* (__fastcall* fnGetLocalPlayer)(int);
	static fnGetLocalPlayer GetLocalPawnFn = (fnGetLocalPlayer)(Utils::Memory::SignatureScan("client.dll", "48 83 EC ? 83 F9 ? 75 ? 48 8B 0D ? ? ? ? 48 8D 54 24 ? 48 8B 01 FF 90 ? ? ? ? 8B 08 48 63 C1 4C 8D 05"));
	return GetLocalPawnFn(-1);
}

float C_CSPlayerPawn::GetInterpolationTiming(int a, int b)
{
	typedef float(__thiscall* oFnGetInterpolationTiming)(C_CSPlayerPawn*, int, int);
	static auto GetInterpolationTiming = (oFnGetInterpolationTiming)Utils::Memory::SignatureScan("client.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 49 63 D8 48 8B F1");
	return GetInterpolationTiming(this, a, b);
}