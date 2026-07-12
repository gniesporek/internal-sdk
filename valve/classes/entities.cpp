#include "classes.h"

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
    Utils::Memory::CallVMT<void>(this, 46, &pBinding); // dynamic vmt because we can't use 1 signature for every entity instance at game (access violation)
    return pBinding;
}
