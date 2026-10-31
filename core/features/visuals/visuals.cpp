#include "../features.h"

void Visuals::Paint()
{
	if (!Variables::Visuals::Enable)
		return;

	if (!Interfaces::pEngineClient->IsInGame() || !Interfaces::pEngineClient->IsConnected()) {
		return;
	}

	auto cachedEntities = Cache::GetEntitiesFromCache();
	if (cachedEntities.empty())
		return;

	for (auto& player : cachedEntities)
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

		if (pPlayerPawn->GetTeamNum() == Globals::LocalPlayerPawn->GetTeamNum() && (!Interfaces::pConVar->GetConVar("mp_teammates_are_enemies") || !Interfaces::pConVar->GetConVar("mp_teammates_are_enemies")->value.i1))
			continue;

		if (!Math::CalculateBoundingBox(pPlayerPawn, bbox, false))
			continue;

		Box(bbox);
		Name(player.pPlayerController, bbox);
		HealthBar(pPlayerPawn, bbox);
		WeaponText(pPlayerPawn, bbox);
		Skeleton(pPlayerPawn);

		// aimbot logic target
		if (Variables::Assistance::Enable && Variables::Assistance::RenderTarget)
		{
			if (!Assistance::GetTargetEntity())
				continue;

			C_CSPlayerPawn* pTargetPawn = Assistance::GetTargetEntity();

			if (!Math::CalculateBoundingBox(pTargetPawn, bbox, false))
				continue;

			int height = Variables::Visuals::Name ? bbox.y - 27 : bbox.y - 15;

			RenderStackSystem::Text::Shadow(ImGui::GetFont(), bbox.x + (bbox.w / 2) - (RenderStackSystem::Text::GetTextWidth(ImGui::GetFont(), "target") / 2), height, "target", Colors(255, 0, 0, 255), Colors::Black(180), 1.f, false);

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

	const char* rawName = pController->GetName();
	if (!rawName)
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

void Visuals::WeaponText(C_CSPlayerPawn* pPawn, BoundingBox bbox)
{
	if (!Variables::Visuals::WeaponText)
		return;

	CPlayer_WeaponServices* pWeaponServices = pPawn->GetWeaponServices();
	if (!pWeaponServices)
		return;

	if (!pWeaponServices->GetWeaponHandle().IsValid())
		return;

	C_BaseEntity* pWeaponEntity = (C_BaseEntity*)EntitySystem::GetEntityByHandle(pWeaponServices->GetWeaponHandle());
	if (!pWeaponEntity)
		return;

	CCStrike15ItemDefinition* ItemSystem = pWeaponEntity->GetAttributeManager().GetEconItemView().GetEconItemSystem();
	if (!ItemSystem)
		return;

	std::string weaponName = ItemSystem->GetName();
	if (weaponName.empty())
		return;

	int textWidth = RenderStackSystem::Text::GetTextWidth(ImGui::GetFont(), weaponName.c_str());

	int centerX = bbox.x + (bbox.w / 2) - (textWidth / 2);

	int drawY = bbox.y + bbox.h + 2;

	RenderStackSystem::Text::Shadow(ImGui::GetFont(), centerX, drawY, weaponName.c_str(), Colors::White(), Colors::Black(180), 1.f, false);
}

void Visuals::Skeleton(C_CSPlayerPawn* pPawn)
{
	if (!Variables::Visuals::Skeleton)
		return;

	CGameSceneNode* pSceneNode = pPawn->GetSceneNode();
	if (!pSceneNode)
		return;

	BoneSystem::CalculateBones((CSkeletonInstance*)pSceneNode, 0xFFFFF);

	CModelState modelState = pSceneNode->GetModelState();

	CBoneData* bonesData = modelState.GetBoneData;
	if (!bonesData)
		return;

	for (auto& pair : bonePairs)
	{
		Vector3D from = bonesData[pair[0]].position;
		Vector3D to = bonesData[pair[1]].position;

		if (from.IsZero() || to.IsZero())
			continue;

		Vector2D screenFrom, screenTo;
		if (Math::WorldToScreen(from, screenFrom) && Math::WorldToScreen(to, screenTo))
		{
			RenderStackSystem::Line::Draw(screenFrom, screenTo, Colors::White());
		}
	}
}