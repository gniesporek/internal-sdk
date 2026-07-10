#include "functions.h"

bool Functions::Setup()
{
	EntitySystem::pEntitySystem = *(EntitySystem**)Utils::Memory::RelativeAddress(Utils::Memory::SignatureScan("client.dll", "48 8B 0D ? ? ? ? E9 ? ? ? ? CC CC 48 8B 89"), 3, 7);
	if (!EntitySystem::pEntitySystem)
		return false;

	MESSAGE_SUCCESS("successfully setup functions");

	return true;
}
