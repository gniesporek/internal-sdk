#include "../features.h"

void Visuals::Overlay(std::vector<Cache::Entities> entities)
{
	for (auto& player : entities)
	{
		if (!player.pPlayerController)
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
	}
}

void Visuals::Box(BoundingBox bbox)
{
	if (!Variables::Visuals::BoundingBox)
		return;

	RenderStackSystem::Rect::Outline(bbox.x, bbox.y, bbox.w, bbox.h, Colors::White(), Colors::Black(150));
}
