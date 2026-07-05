#pragma once

class CEngineClient
{
public:
	bool isInGame()
	{
		typedef bool(__thiscall* fnIsInGame)(CEngineClient*);
		static auto isInGameFn = (fnIsInGame)(utils.memory.signatureScan("engine2.dll", "48 8B 05 ? ? ? ? 48 85 C0 74 ? 80 B8 ? ? ? ? ? 75 ? 83 B8 ? ? ? ? ? 7C"));
		return isInGameFn(this);
	}
	bool isConnected()
	{
		typedef bool(__thiscall* fnIsConnected)(CEngineClient*);
		static auto isConnectedFn = (fnIsConnected)(utils.memory.signatureScan("engine2.dll", "48 8B 05 ? ? ? ? 48 85 C0 74 ? 83 B8 ? ? ? ? ? 0F 9D C0"));
		return isConnectedFn(this);
	}
};