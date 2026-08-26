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

CHitboxSet* C_CSPlayerPawn::GetHitboxSet()
{
	// 48 89 5C 24 08 48 89 74 24 10 57 48 81 EC 40 01 00 00 8B DA 48 8B F9 E8 ?? ?? ?? ?? client.dll
	typedef CHitboxSet* (__thiscall* oFnGetHitboxSet)(C_CSPlayerPawn*, int);
	static auto GetHitboxSet = (oFnGetHitboxSet)Utils::Memory::SignatureScan("client.dll", "48 89 5C 24 08 48 89 74 24 10 57 48 81 EC 40 01 00 00 8B DA 48 8B F9 E8 ?? ?? ?? ??");
	if (!GetHitboxSet)
		return nullptr;

	return GetHitboxSet(this, 0);
}


int C_CSPlayerPawn::HitboxToWorldTransform(CHitboxSet* hitboxSet, Transform_t* transform)
{
	// 48 89 5C 24 18 55 56 57 41 56 41 57 48 83 EC 20 41
	typedef int(__thiscall* fnHitboxToWorldTransform)(C_CSPlayerPawn*, CHitboxSet*, Transform_t*, int);
	static auto HitboxToWorldTransform = (fnHitboxToWorldTransform)(Utils::Memory::SignatureScan("client.dll", "48 89 5C 24 18 55 56 57 41 56 41 57 48 83 EC 20 41"));
	if (HitboxToWorldTransform)
		return HitboxToWorldTransform(this, hitboxSet, transform, 1024);

	return 0;
}