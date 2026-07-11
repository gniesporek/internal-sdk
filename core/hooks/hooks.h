#pragma once
#include "../utils/utils.h"

#include "../../valve/interfaces/interfaces.h"

#include "../../ext/minhook/minhook.h"

#include "../ui/ui.h"

#include "../cache/cache.h"

#include "directx11/directx11.h"
#include "engine2/engine2.h"
#include "client/mouse_input.h"
#include "input_system/input_system.h"

#include "../features/features.h"

class HooksManager {
public:
	static bool Setup();
	static void Destroy();
private:
	template<typename T>
	static void CreateHook(const std::string& name, const char* moduleName, const char* pattern, bool relative, T** original, void* detour);
};
