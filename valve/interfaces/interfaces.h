#pragma once
#include "../../core/utils/utils.h"

#include "schema_system.h"

class Interfaces {
public:
	ISchemaSystem* schemaSystem = nullptr;

	bool setup();
private:
	void* getInterface(const char* moduleName, const char* interfaceName);
};

inline Interfaces interfaces;