#pragma once
#include "../../core/utils/utils.h"

#include "schema_system.h"
#include "engine_client.h"
#include "input_system.h"

class Interfaces {
public:
	static inline ISchemaSystem* pSchemaSystem = nullptr;
	static inline CInputSystem* pInputSystem = nullptr;
	static inline CEngineClient* pEngineClient = nullptr;

	static bool Setup();
private:
	static void* GetInterface(const char* moduleName, const char* interfaceName);
};