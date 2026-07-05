#include "../hooks.h"

#include "../../renderer/drawing.h"

void __fastcall OnClientOutput::hkOnClientOutput(__int64 a1, __int64 a2)
{
	if (renderer.isRendererReady)
	{
		renderStackSystem.clearDrawData();

		renderStackSystem.swapDrawData();
	}

	oOnClientOutput(a1, a2);
}
