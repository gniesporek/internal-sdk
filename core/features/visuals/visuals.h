#pragma once

class Visuals {
public:
	static void Paint();
private:
	static void Box(BoundingBox bbox);
	static void Name(CCSPlayerController* pController, BoundingBox bbox);
	static void HealthBar(C_CSPlayerPawn* pPlayerPawn, BoundingBox bbox);
	static void WeaponText(C_CSPlayerPawn* pPawn, BoundingBox bbox);
	static void Skeleton(C_CSPlayerPawn* pPawn);

	// skeleton connection
    static inline const int bonePairs[][2] = {
        { BONE_HEAD_0, BONE_NECK_0 },
        { BONE_NECK_0, BONE_SPINE_3 },
        { BONE_SPINE_3, BONE_SPINE_2 },
        { BONE_SPINE_2, BONE_PELVIS },
        { BONE_PELVIS, BONE_LEG_UPPER_L },
        { BONE_PELVIS, BONE_LEG_UPPER_R },
        { BONE_NECK_0, BONE_ARM_UPPER_L },
        { BONE_ARM_UPPER_L, BONE_ARM_LOWER_L },
        { BONE_ARM_LOWER_L, BONE_HAND_L },

        { BONE_NECK_0, BONE_ARM_UPPER_R },
        { BONE_ARM_UPPER_R, BONE_ARM_LOWER_R },
        { BONE_ARM_LOWER_R, BONE_HAND_R },

        { BONE_LEG_UPPER_L, BONE_LEG_LOWER_L },
        { BONE_LEG_LOWER_L, BONE_ANKLE_L },
        { BONE_LEG_UPPER_R, BONE_LEG_LOWER_R },
        { BONE_LEG_LOWER_R, BONE_ANKLE_R },
    };
};