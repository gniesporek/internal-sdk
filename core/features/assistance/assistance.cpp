#include "../features.h"

#include "../../../valve/functions/hitbox_system.h"
#include "../../../valve/functions/trace_manager.h"

void Assistance::Run(CUserCmd* pCommand)
{

	if (!Interfaces::pEngineClient->IsInGame() || !Interfaces::pEngineClient->IsConnected())
		return;

	if (!Variables::Assistance::Enable)
		return;

	PlayerInformation::pTargetEntity = nullptr;

	auto cachedEntities = Cache::GetEntitiesFromCache();
	if (cachedEntities.empty())
		return;

	PenetrationData penData = {};

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

		PlayerInformation::pTargetEntity = pPawn;
	}


	if (PlayerInformation::pTargetEntity)
	{
		Vector3D hitboxPosition = HitboxSystem::GetHitboxPosition(PlayerInformation::pTargetEntity, HITBOX_HEAD);
		Vector3D localEyePosition = Globals::PredictedEyePosition;
		Vector3D angle = Math::CalculateAngle(localEyePosition, hitboxPosition);


		if (!Globals::ActiveWeapon)
			return;

		if (PenetrationSystem::SimulateFireBullet(localEyePosition, hitboxPosition, PlayerInformation::pTargetEntity, Globals::ActiveWeapon, penData))
		{
			if (penData.Damage >= 100) // sanity check 
			{
			
				if (!Variables::Assistance::SilentAim)
				{
					Interfaces::pCSGOInput->SetViewAngles(angle);
				}

				pCommand->SetInputHistory(&angle, Globals::LocalPlayerController, PlayerInformation::pTargetEntity);

				if (Variables::Assistance::AutoShoot) {
				
					if (Globals::ActiveWeapon->CanFire())
					{
						pCommand->CSGOUserCmd.Attack1StartHistoryIndex = 0;
						pCommand->CSGOUserCmd.SetBits(CSGOUSERCMD_BITS_ATTACK1_START_HISTORY_INDEX);
						pCommand->ButtonState.Value |= IN_ATTACK;
					
					}
				}
			}
		}
	}

}
