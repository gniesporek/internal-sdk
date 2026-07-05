#include "interfaces.h"

bool Interfaces::setup()
{
	schemaSystem = (ISchemaSystem*)getInterface("schemasystem.dll", "SchemaSystem_001");
	engineClient = (CEngineClient*)getInterface("engine2.dll", "Source2EngineToClient001");
	inputSystem = (CInputSystem*)getInterface("inputsystem.dll", "InputSystemVersion001");

	return true;
}

void* Interfaces::getInterface(const char* moduleName, const char* interfaceName)
{
	typedef void* (__fastcall* createInterfaceFn)(const char*, int*);

	auto pHandle = GetModuleHandleA(moduleName);
	if (!pHandle)
		return NULL;

	auto createInterface = (createInterfaceFn)GetProcAddress(pHandle, "CreateInterface");
	if (!createInterface)
		return NULL;

	void* pInterface = createInterface(interfaceName, 0);
	if (!pInterface)
		return NULL;

	MESSAGE_INFO("found interface %s" , interfaceName);

	return pInterface;
}
