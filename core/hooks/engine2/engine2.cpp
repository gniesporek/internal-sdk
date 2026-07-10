#include "../hooks.h"

#include "../../renderer/drawing.h"

void __fastcall OnClientOutput::hkOnClientOutput(__int64 a1, __int64 a2)
{
	if (Renderer::m_bInitialized)
	{
		RenderStackSystem::ClearDrawData();

		RenderStackSystem::Text::Shadow(ImGui::GetFont(), Vector2D(10, 10), "welcome", Colors::White(), Colors::Black(150), 1.f, false);

		Features::Drawing::Paint();

		RenderStackSystem::SwapDrawData();
	}

	oOnClientOutput(a1, a2);
}
