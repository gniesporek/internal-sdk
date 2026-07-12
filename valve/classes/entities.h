#pragma once

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

class CGameSceneNode {
public:
    SCHEMA("CGameSceneNode", "m_vecAbsOrigin", GetAbsOrigin, Vector3D)
};

class C_BaseEntity : public CEntityInstance
{
public:
    bool IsEntityPlayerController();
    bool IsEntityPlayer();
    bool ComputeHitboxSurroundingBox(Vector3D* mins, Vector3D* maxs);
    SCHEMA("C_BaseEntity","m_iHealth", GetHealth,int)
    SCHEMA("C_BaseEntity", "m_pGameSceneNode",GetSceneNode,CGameSceneNode*)
    SCHEMA("C_BaseEntity","m_pCollision",GetCollisionProperty,CCollisionProperty*)

};