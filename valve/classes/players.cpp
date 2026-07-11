#include "classes.h"

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
