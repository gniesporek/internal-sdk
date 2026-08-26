#pragma once

class CHitboxSet;

class CCSPlayerController
{
public:
	SCHEMA("CBasePlayerController", "m_hPawn", GetPawnHandle, C_BaseHandle)
	SCHEMA("CBasePlayerController", "m_nTickBase", GetTickBase, uint32_t)
	SCHEMA("CCSPlayerController", "m_sSanitizedPlayerName", GetName, const char*)
	
	uint32_t SetTickBase(uint32_t tickBase);
	static CCSPlayerController* GetLocalPlayer(); 
};

class C_CSPlayerPawn : public C_BaseEntity {
public:
	static C_CSPlayerPawn* GetLocalPlayer();
	float GetInterpolationTiming(int a, int b);
	CHitboxSet* GetHitboxSet();
	int HitboxToWorldTransform(CHitboxSet* hitboxSet, Transform_t* transform);
};