#pragma once

#include "classes/classes.h"

class Globals {
public:
	static inline C_CSPlayerPawn* LocalPlayerPawn = nullptr;
	static inline CCSPlayerController* LocalPlayerController = nullptr;
	static inline C_CSWeapon* ActiveWeapon = nullptr;
	static inline Vector3D PredictedEyePosition = Vector3D(0, 0, 0);
};