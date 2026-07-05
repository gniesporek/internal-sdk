#pragma once
#include "../../core/utils/utils.h"

#include "schema_system.h"

class Interfaces {
public:
	ISchemaSystem* pSchemaSystem = nullptr;

	bool setup();
private:
	void* get_interface(const char* module_name, const char* interface_name);
};

inline Interfaces interfaces;