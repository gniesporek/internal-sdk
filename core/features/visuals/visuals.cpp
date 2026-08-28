#include "../features.h"

void Visuals::Overlay(std::vector<Cache::Entities> entities)
{
	for (auto& player : entities)
	{
		if (!player.pPlayerController)
			continue;

		if (!player.pPlayerController->GetPawnHandle().IsValid())
			continue;

		C_CSPlayerPawn* pPlayerPawn = (C_CSPlayerPawn*)EntitySystem::GetEntityByHandle(player.pPlayerController->GetPawnHandle());
		if (!pPlayerPawn)
			continue;
		
		if (!pPlayerPawn->IsEntityPlayer())
			continue;

		if(!pPlayerPawn->IsEntityAlive())
			continue;

		if (!Math::CalculateBoundingBox(pPlayerPawn, bbox, false))
			continue;

		Box(bbox);
		Name(player.pPlayerController, bbox);
		HealthBar(pPlayerPawn, bbox);


		// aimbot logic target
		if (Variables::Assistance::Enable && Variables::Assistance::RenderTarget)
		{
			if (!Assistance::GetTargetEntity())
				return;

			C_CSPlayerPawn* pTargetPawn = Assistance::GetTargetEntity();

			if (!Math::CalculateBoundingBox(pTargetPawn, bbox, false))
				continue;

			RenderStackSystem::Text::Shadow(ImGui::GetFont(), bbox.x + (bbox.w / 2) - (RenderStackSystem::Text::GetTextWidth(ImGui::GetFont(), "target") / 2), bbox.y - 15, "target", Colors(255, 0, 0, 255), Colors::Black(180), 1.f, false);

		}

	}
}

void Visuals::Box(BoundingBox bbox)
{
	if (!Variables::Visuals::BoundingBox)
		return;

	RenderStackSystem::Rect::Outline(bbox.x, bbox.y, bbox.w, bbox.h, Colors::White(), Colors::Black(150));
}

void Visuals::Name(CCSPlayerController* pController, BoundingBox bbox)
{
	if (!Variables::Visuals::Name)
		return;

	std::string playerName = pController->GetName();
	if (playerName.empty())
		return;
	
	const int textWidth = RenderStackSystem::Text::GetTextWidth(ImGui::GetFont(), playerName.c_str());
	const int centerX = bbox.x + (bbox.w / 2) - (textWidth / 2);

	RenderStackSystem::Text::Shadow(ImGui::GetFont(), centerX, bbox.y - 15, playerName.c_str(), Colors::White(), Colors::Black(180), 1.f, false);

}

void Visuals::HealthBar(C_CSPlayerPawn* pPlayerPawn, BoundingBox bbox)
{
	if (!Variables::Visuals::Health)
		return;

	const int health = pPlayerPawn->GetHealth();
	const int maxHealth = pPlayerPawn->GetMaxHealth();

	if (maxHealth <= 0)
		return;

	const float healthRatio = std::clamp(static_cast<float>(health) / static_cast<float>(maxHealth), 0.0f, 1.0f);

	Colors healthColor;
	healthColor.r = static_cast<int>((1.0f - healthRatio) * 255 + healthRatio * 145);
	healthColor.g = static_cast<int>(healthRatio * 205);
	healthColor.b = static_cast<int>(healthRatio * 120);
	healthColor.a = 255;

	Colors backgroundColor(46, 46, 46, 255);
	Colors outlineColor(0, 0, 0, 255);

	int barHeight = std::round(bbox.h * healthRatio);
	barHeight = std::clamp(barHeight, 0, bbox.h);

	int barY = bbox.y + (bbox.h - barHeight);
	int barX = bbox.x - 4;
	int barWidth = 1;

	RenderStackSystem::Rect::Fill(barX - 1, bbox.y - 1, barWidth + 2, bbox.h + 2, outlineColor);
	RenderStackSystem::Rect::Fill(barX, bbox.y, barWidth, bbox.h, backgroundColor);
	RenderStackSystem::Rect::Fill(barX, barY, barWidth, barHeight, healthColor);
}