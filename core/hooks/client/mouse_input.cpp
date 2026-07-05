#include "../hooks.h"

bool __fastcall MouseInput::hkMouseInput(void* a1)
{
	if (UI::Toggled)
		return false;

	return oMouseInput(a1);
}