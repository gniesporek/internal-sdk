#include "../hooks.h"

void __fastcall RelativeMouseMode::hkSetRelativeMouseMode(void* _this, bool enable)
{
	if (ui.isToggled)
		return oSetRelativeMouseMode(_this, false);

	return oSetRelativeMouseMode(_this, enable);
}
