#pragma once

#include "../../../valve/structs/c_user_cmd.h"

class Assistance {
public:
	static void Run(CUserCmd* pCommand);

	static inline C_CSPlayerPawn* GetTargetEntity() { return PlayerInformation::pTargetEntity; }
private:
	struct PlayerInformation {
	public:
		static inline C_CSPlayerPawn* pTargetEntity = nullptr;
	};

};