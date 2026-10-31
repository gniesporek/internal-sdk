#include "bone_system.h"

#include "../../core/utils/utils.h"

void BoneSystem::CalculateBones(CSkeletonInstance* pSkeleton, int mask)
{
	typedef void(__fastcall* fnCalculateBones)(CSkeletonInstance*, int mask);
	static fnCalculateBones CalculateBones = (fnCalculateBones)(Utils::Memory::RelativeAddress(Utils::Memory::SignatureScan("client.dll", "E8 ? ? ? ? 4C 8B A3 ? ? ? ? 33 F6"), 1, 5));
	
	if (!CalculateBones)
		return;

	CalculateBones(pSkeleton, mask);
};
