#pragma once

#include "../../../valve/structs/c_csgo_input.h"

class CreateMove
{
public:
	typedef void(__fastcall* oFnCreateMove)(CCSGOInput* a1, int a2, char a3);
	static inline oFnCreateMove oCreateMove = nullptr;
	static void hkCreateMove(CCSGOInput* a1, int a2, char a3);
};