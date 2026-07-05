#pragma once

class CEngineClient
{
public:
	bool IsInGame()
	{
		typedef bool(__thiscall* fnIsInGame)(CEngineClient*);
		static auto IsInGameFn = (fnIsInGame)(Utils::Memory::SignatureScan("engine2.dll", "48 8B 05 ? ? ? ? 48 85 C0 74 ? 80 B8 ? ? ? ? ? 75 ? 83 B8 ? ? ? ? ? 7C"));
		return IsInGameFn(this);
	}
	bool IsConnected()
	{
		typedef bool(__thiscall* fnIsConnected)(CEngineClient*);
		static auto IsConnectedFn = (fnIsConnected)(Utils::Memory::SignatureScan("engine2.dll", "48 8B 05 ? ? ? ? 48 85 C0 74 ? 83 B8 ? ? ? ? ? 0F 9D C0"));
		return IsConnectedFn(this);
	}
};