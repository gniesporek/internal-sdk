#pragma once
#include "../../core/utils/utils.h"

#include "schema_system.h"
#include "engine_client.h"
#include "input_system.h"

class Interfaces {
public:
	ISchemaSystem* schemaSystem = nullptr;
	CInputSystem* inputSystem = nullptr;
	CEngineClient* engineClient = nullptr;

	bool setup();
private:
	void* getInterface(const char* moduleName, const char* interfaceName);
};

inline Interfaces interfaces;