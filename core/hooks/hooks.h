#pragma once
#include "../utils/utils.h"

#include "../../valve/interfaces/interfaces.h"

#include "../../ext/minhook/minhook.h"

#include "directx11/directx11.h"
#include "engine2/engine2.h"

class HooksManager {
public:
	bool setup();
	void destroy();
private:
	template<typename T>
	void createHook(const std::string& name, const char* moduleName, const char* pattern, bool relative, T** original, void* detour);
};
inline HooksManager hooksManager;