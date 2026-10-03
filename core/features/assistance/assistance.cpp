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


	static CConVar* mpTeammatesAreEnemies = nullptr;

	if (!mpTeammatesAreEnemies)
		mpTeammatesAreEnemies = Interfaces::pConVar->GetConVar("mp_teammates_are_enemies");

	// find target etc

	for (auto& entity : cachedEntities)
	{
		if (!entity.pPlayerController)
			continue;

		if (!entity.pPlayerController->GetPawnHandle().IsValid())
			continue;

		C_CSPlayerPawn* pPawn = (C_CSPlayerPawn*)(EntitySystem::GetEntityByHandle(entity.pPlayerController->GetPawnHandle()));
		if (!pPawn->IsEntityPlayer())
			continue;

		if (!pPawn->IsEntityAlive())
			continue;

		if (pPawn == Globals::LocalPlayerPawn)
			continue;
	
		if (pPawn->GetTeamNum() == Globals::LocalPlayerPawn->GetTeamNum() && (!mpTeammatesAreEnemies || !mpTeammatesAreEnemies->value.i1))
			continue;

		PlayerInformation::pTargetEntity = pPawn;
	}


	if (PlayerInformation::pTargetEntity)
	{
		Vector3D hitboxPosition = HitboxSystem::GetHitboxPosition(PlayerInformation::pTargetEntity, HITBOX_HEAD);
		Vector3D localEyePosition = Globals::LocalPlayerPawn->GetEyePosition();
		Vector3D angle = Math::CalculateAngle(localEyePosition, hitboxPosition);


		if (!Globals::ActiveWeapon)
			return;

		if (PenetrationSystem::SimulateFireBullet(localEyePosition, hitboxPosition, PlayerInformation::pTargetEntity, Globals::ActiveWeapon, penData))
		{
			if (penData.Damage > 0)
			{
				Interfaces::pCSGOInput->SetViewAngles(angle);

			}
		}


	}

}
