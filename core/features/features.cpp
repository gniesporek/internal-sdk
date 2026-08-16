#include "features.h"

void Features::Drawing::Paint()
{
	if (!Interfaces::pEngineClient->IsInGame())
		return;

	if (!Variables::Visuals::Enable)
		return;

	auto cachedEntities = Cache::GetEntitiesFromCache();
	if (cachedEntities.empty())
		return;

	Visuals::Overlay(cachedEntities);
}
