#pragma once

class MouseInput
{
public:
	typedef bool(__fastcall* ofnMouseInput)(void*);
	static bool __fastcall hkMouseInput(void* a1);
	static inline ofnMouseInput oMouseInput = nullptr;
};