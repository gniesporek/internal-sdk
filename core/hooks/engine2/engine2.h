#pragma once

class OnClientOutput {
public:
	typedef void(__fastcall* fnOnClientOutput)(__int64 a1, __int64 a2);
	static void __fastcall hkOnClientOutput(__int64 a1, __int64 a2);
	static inline fnOnClientOutput oOnClientOutput;
};