#pragma once

class CCSPlayerController
{
public:
	SCHEMA("CBasePlayerController", "m_hPawn", GetPawnHandle, C_BaseHandle)

	static CCSPlayerController* GetLocalPlayer(); 
};

class C_CSPlayerPawn : public C_BaseEntity {
public:
	static C_CSPlayerPawn* GetLocalPlayer();

};