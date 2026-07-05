#pragma once

class RelativeMouseMode {
public:
	typedef void(__fastcall* fnSetRelativeMouseMode)(void* _this, bool enable);
	static void __fastcall hkSetRelativeMouseMode(void* _this, bool enable);
	static inline fnSetRelativeMouseMode oSetRelativeMouseMode;
};