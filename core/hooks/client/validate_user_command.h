#pragma once

class ValidateUserCommand {
public:
	typedef void(__fastcall* OriginalFn)(CCSGOInput*, int);
	static inline OriginalFn oValidateUserCommand = nullptr;
	static void __fastcall hkValidateUserCommand(CCSGOInput* input, int slot);
};