#include "../features.h"

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

	// find target etc

}
