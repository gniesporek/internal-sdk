#include "classes.h"

bool C_BaseEntity::IsEntityPlayerController()
{
    if (FNV1A::Hash(this->GetSchemaClassBinding()->szName) == FNV1A::Hash("CCSPlayerController"))
        return true;

    return false;
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
