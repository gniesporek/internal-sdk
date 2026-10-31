#pragma once

class CUserCmd;

class C_BaseHandle
{
public:
    C_BaseHandle()
        : nIndex(0xFFFFFFFF) {}

    explicit C_BaseHandle(uint32_t rawHandle)
        : nIndex(rawHandle) {}

    bool IsValid() const
    {
        return nIndex != 0xFFFFFFFF;
    }

    int GetEntryIndex() const
    {
        return nIndex & 0x7FFF;
    }

private:
    uint32_t nIndex;
};

class CCStrike15ItemDefinition
{
public:
    PAD_OFFSET(const char*, GetSFUIItemName, 0x70);
    PAD_OFFSET(const char*, GetName, 0x260);
};

class C_EconItemView {
public:
    CCStrike15ItemDefinition* GetEconItemSystem();
	SCHEMA("C_EconItemView", "m_iItemDefinitionIndex", GetDefinitionIndex, UINT16)
};

class C_AttributeContainer {
public:
	SCHEMA("C_AttributeContainer", "m_Item", GetEconItemView, C_EconItemView)
};

class CPlayer_WeaponServices {
public:
    SCHEMA("CPlayer_WeaponServices","m_hActiveWeapon",GetWeaponHandle,C_BaseHandle)
};

class CCSWeaponBaseVData {
public:
    SCHEMA("CCSWeaponBaseVData","m_flPenetration",GetPenetration,float)
    SCHEMA("CCSWeaponBaseVData", "m_nDamage", GetBaseDamage, int)
    SCHEMA("CCSWeaponBaseVData", "m_flRange", GetRange, float)
    SCHEMA("CCSWeaponBaseVData", "m_flRangeModifier", GetRangeModifier, float)
    SCHEMA("CCSWeaponBaseVData", "m_flArmorRatio", GetArmorRatio, float)
    SCHEMA("CCSWeaponBaseVData", "m_flHeadshotMultiplier", GetHeadshotMultiplier, float)
    SCHEMA("CCSWeaponBaseVData", "m_bReloadsSingleShells", IsReloadingSingle, bool)
};

class C_CSWeapon {
public:
    SCHEMA("C_CSWeaponBase","m_bInReload",IsReloading,bool)
    SCHEMA("C_BasePlayerWeapon", "m_iClip1", GetClip, int)
    SCHEMA("C_BasePlayerWeapon", "m_nNextPrimaryAttackTick",GetNextPrimaryAttackTick,int)
    CCSWeaponBaseVData* GetWeaponData();
    void UpdateAccuracy();
    bool CanFire();
};

class CPlayer_ItemServices {
public:
    SCHEMA("CCSPlayer_ItemServices", "m_bHasHelmet", HasHelmet, bool)
    bool HasPlayerArmor(int hitGroup);
};

class CEntityInstance {
public:
    CSchemaClassBinding* GetSchemaClassBinding();
};

class CCollisionProperty
{
public:
    SCHEMA("CCollisionProperty","m_vecMins",GetMins,Vector3D)
    SCHEMA("CCollisionProperty","m_vecMaxs",GetMaxs,Vector3D)
};

class alignas(16) CBoneData {
public:
    Vector3D position;
    float scale;
    Vector3D rotation;
};

class CModelState {
public:
    PAD(0x80);
    CBoneData* GetBoneData;
};

class CSkeletonInstance
{
public:
    SCHEMA("CSkeletonInstance","m_modelState",GetModelState,CModelState)
};

class CGameSceneNode : public CSkeletonInstance {
public:
    SCHEMA("CGameSceneNode", "m_vecAbsOrigin", GetAbsOrigin, Vector3D)
};

class CPlayerMovementServices {
public:
    void SetPredictionData(CUserCmd* pCommand);
	void ResetPredictionData();
};

class C_BaseEntity : public CEntityInstance
{
public:
    bool IsEntityPlayerController();
    bool IsEntityPlayer();
    bool ComputeHitboxSurroundingBox(Vector3D* mins, Vector3D* maxs);
    bool IsEntityAlive();
    Vector3D GetEyePosition();
	Vector3D GetShootPosition();
    Vector3D GetPunchAngle();
    SCHEMA("C_BaseModelEntity","m_vecViewOffset",GetViewOffset,Vector3D)
    SCHEMA("C_BaseEntity","m_iHealth", GetHealth,int)
	SCHEMA("C_BaseEntity", "m_iMaxHealth", GetMaxHealth, int)
    SCHEMA("C_BaseEntity", "m_pGameSceneNode",GetSceneNode,CGameSceneNode*)
    SCHEMA("C_BaseEntity","m_pCollision",GetCollisionProperty,CCollisionProperty*)
    SCHEMA("C_BaseEntity","m_iTeamNum",GetTeamNum,int)
	SCHEMA("C_BaseEntity", "m_flSimulationTime", GetSimulationTime, float)
    SCHEMA("C_EconEntity","m_AttributeManager",GetAttributeManager,C_AttributeContainer)
    SCHEMA("C_BaseEntity","m_fFlags",GetFlags, int32_t)
};