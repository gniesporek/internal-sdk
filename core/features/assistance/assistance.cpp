#include "../features.h"

#include "../../../valve/functions/hitbox_system.h"
#include "../../../valve/functions/trace_manager.h"

void Assistance::Run(CUserCmd* pCommand)
{

	if (!Interfaces::pEngineClient->IsInGame() || !Interfaces::pEngineClient->IsConnected())
		return;

	if (!Variables::Assistance::Enable)
		return;

	if (!Globals::LocalPlayerPawn->IsEntityAlive())
		return;

	PlayerInformation::pTargetEntity = nullptr;

	auto cachedEntities = Cache::GetEntitiesFromCache();
	if (cachedEntities.empty())
		return;

	PenetrationData penData = {};

	float best = FLT_MAX;
	Vector2D center(ImGui::GetIO().DisplaySize.x / 2, ImGui::GetIO().DisplaySize.y / 2);

	// find target etc

	for (auto& entity : cachedEntities)
	{
		if (!entity.pPlayerController)
			continue;

		if (!entity.pPlayerController->GetPawnHandle().IsValid())
			continue;

		C_CSPlayerPawn* pPawn = (C_CSPlayerPawn*)(EntitySystem::GetEntityByHandle(entity.pPlayerController->GetPawnHandle()));
		if (!pPawn)
			continue;

		if (!pPawn->IsEntityPlayer())
			continue;

		if (!pPawn->IsEntityAlive())
			continue;

		if (pPawn == Globals::LocalPlayerPawn)
			continue;
	
		if (pPawn->GetTeamNum() == Globals::LocalPlayerPawn->GetTeamNum() && (!Interfaces::pConVar->GetConVar("mp_teammates_are_enemies") || !Interfaces::pConVar->GetConVar("mp_teammates_are_enemies")->value.i1))
			continue;

		Vector3D hitboxPosition = HitboxSystem::GetHitboxPosition(pPawn, HITBOX_HEAD);

		Vector2D screen;
		if (!Math::WorldToScreen(hitboxPosition, screen))
			continue;

		float distanceToCrosshair = screen.DistanceTo(center);

		if (distanceToCrosshair < best)
		{
			best = distanceToCrosshair;

			PlayerInformation::pTargetEntity = pPawn;
			PlayerInformation::TargetHitboxPosition = hitboxPosition;
		}
	}

	if (PlayerInformation::pTargetEntity)
	{
		Vector3D localEyePosition = Globals::PredictedEyePosition;
		Vector3D angle = Math::CalculateAngle(localEyePosition, PlayerInformation::TargetHitboxPosition);

		angle -= Globals::LocalPlayerPawn->GetPunchAngle();

		angle.Normalize();

		if (!Globals::ActiveWeapon)
			return;

		if (PenetrationSystem::SimulateFireBullet(localEyePosition, PlayerInformation::TargetHitboxPosition, PlayerInformation::pTargetEntity, Globals::ActiveWeapon, penData))
		{
			if (penData.Damage >= 101) // sanity check 
			{
			
				if (!Variables::Assistance::SilentAim)
				{
					Interfaces::pCSGOInput->SetViewAngles(angle);
				}

				pCommand->SetInputHistory(&angle, Globals::LocalPlayerController, PlayerInformation::pTargetEntity);

				if (Variables::Assistance::AutoShoot) {
				
					if (Globals::ActiveWeapon->CanFire())
					{
						pCommand->CSGOUserCmd.Attack1StartHistoryIndex = pCommand->CSGOUserCmd.InputHistoryEntry.nCurrentSize - 1;
						pCommand->CSGOUserCmd.SetBits(CSGOUSERCMD_BITS_ATTACK1_START_HISTORY_INDEX);
						pCommand->ButtonState.Value |= IN_ATTACK;
					
					}
				}
			}
		}
	}

}
