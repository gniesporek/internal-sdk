#include "interfaces.h"

bool Interfaces::setup()
{
	pSchemaSystem = (ISchemaSystem*)get_interface("schemasystem.dll", "SchemaSystem_001");

	return true;
}

void* Interfaces::get_interface(const char* module_name, const char* interface_name)
{
	typedef void* (__fastcall* CreateInterfaceFn)(const char*, int*);

	auto pHandle = GetModuleHandleA(module_name);
	if (!pHandle)
		return NULL;

	auto CreateInterface = (CreateInterfaceFn)GetProcAddress(pHandle, "CreateInterface");
	if (!CreateInterface)
		return NULL;

	void* Interface = CreateInterface(interface_name, 0);
	if (!Interface)
		return NULL;

	MESSAGE_INFO("found interface %s" , interface_name);

	return Interface;
}
