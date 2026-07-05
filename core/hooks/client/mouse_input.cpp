#include "../hooks.h"

bool __fastcall MouseInput::hkMouseInput(void* a1)
{
	if (ui.isToggled)
		return false;

	return oMouseInput(a1);
}