#include "classes.h"

#include "../functions/trace_manager.h"

bool C_BaseEntity::IsEntityPlayerController()
{
    if (FNV1A::Hash(this->GetSchemaClassBinding()->szName) == FNV1A::Hash("CCSPlayerController"))
        return true;

    return false;
}

bool C_BaseEntity::IsEntityPlayer()
{
    if (FNV1A::Hash(this->GetSchemaClassBinding()->szName) == FNV1A::Hash("C_CSPlayerPawn"))
        return true;

    return false;
}

bool C_BaseEntity::ComputeHitboxSurroundingBox(Vector3D* mins, Vector3D* maxs)
{
    // https://imgur.com/a/qQVFft7
    // char __fastcall ComputeHitboxSurroundingBox(__int64 a1, unsigned __int64 *a2, float *a3)

    typedef bool(__fastcall* fnComputeHitboxSurroundingBox)(C_BaseEntity*, Vector3D*, Vector3D*);
    static auto ComputeHitboxSurroundingBoxFn = (fnComputeHitboxSurroundingBox)(Utils::Memory::SignatureScan("client.dll", "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B FA"));
    return ComputeHitboxSurroundingBoxFn(this, mins, maxs);

}

bool C_BaseEntity::IsEntityAlive()
{
    return this->GetHealth() > 0;
}

Vector3D C_BaseEntity::GetEyePosition()
{
    return this->GetViewOffset() + this->GetSceneNode()->GetAbsOrigin();
}

CSchemaClassBinding* CEntityInstance::GetSchemaClassBinding()
{
    /*
    __int64 __fastcall sub_150FFB0(__int64 a1, __int64 a2)
    {
            nullsub_1001();
            unknown_libname_427(a2, &unk_20D22D0);
            return a2;
        }
    */

    CSchemaClassBinding* pBinding = nullptr;
    Utils::Memory::CallVMT<void>(this, 47, &pBinding); // dynamic vmt because we can't use 1 signature for every entity instance at game (access violation)
    return pBinding;
}

void CPlayerMovementServices::SetPredictionData(CUserCmd* pCommand)
{
    typedef void(__thiscall* fnSetPredictionData)(CPlayerMovementServices*, CUserCmd*);
    static auto SetPredictionData = (fnSetPredictionData)(Utils::Memory::SignatureScan("client.dll", "48 89 5C 24 ? 57 48 83 EC ? 48 8B DA E8 ? ? ? ? 48 8B F8 48 85 C0 74"));
    SetPredictionData(this, pCommand);
}

void CPlayerMovementServices::ResetPredictionData()
{
    typedef void(__thiscall* fnResetPredictionData)(CPlayerMovementServices*);
    static auto ResetPredictionData = (fnResetPredictionData)(Utils::Memory::SignatureScan("client.dll", "48 83 EC ? B9 ? ? ? ? E8 ? ? ? ? 48 C7 05"));
    ResetPredictionData(this);
}

CCSWeaponBaseVData* C_CSWeapon::GetWeaponData()
{
    static const auto offset = *(uint32_t*)(Utils::Memory::SignatureScan("client.dll", "48 8B 81 ? ? ? ? 48 8B 88 ? ? ? ? 48 8D 05") + 3);
    return *(CCSWeaponBaseVData**)(std::uintptr_t(this) + offset);
}

void C_CSWeapon::UpdateAccuracy()
{
    typedef void(__thiscall* fnUpdateAccuracyPenalty)(C_CSWeapon*);
    static auto UpdateAccuracyPenalty = (fnUpdateAccuracyPenalty)(Utils::Memory::SignatureScan("client.dll", "40 57 41 56 48 83 EC ? 48 8B F9"));
    UpdateAccuracyPenalty(this);
}

bool C_CSWeapon::CanFire()
{
    CCSWeaponBaseVData* weaponInfo = this->GetWeaponData();
    if (!weaponInfo)
        return false;

    bool IsWeaponReloading = this->IsReloading() && !weaponInfo->IsReloadingSingle();
    if (IsWeaponReloading)
        return false;

    if (this->GetClip() <= 0)
        return false;

    float serverTime = Globals::LocalPlayerController->GetTickBase() * 0.015625f;

    float nextAttack = this->GetNextPrimaryAttackTick() * 0.015625f;
    return serverTime >= nextAttack;
}

bool CPlayer_ItemServices::HasPlayerArmor(int hitGroup)
{
    switch (hitGroup)
    {
    case HITGROUP_HEAD:
        return this->HasHelmet();
        break;
    case HITGROUP_GENERIC:
    case HITGROUP_CHEST:
    case HITGROUP_STOMACH:
    case HITGROUP_LEFTARM:
    case HITGROUP_RIGHTARM:
        return Globals::LocalPlayerPawn->GetArmor() > 0.f;
        break;
    default:
        return false;
    }
}
