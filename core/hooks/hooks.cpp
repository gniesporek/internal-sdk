#include "hooks.h"

bool HooksManager::setup()
{
    if (MH_Initialize() != MH_OK) {
        MESSAGE_ERROR("failed to initialize minhook");
        return false;
    }

    createHook("PresentScene", "gameoverlayRenderer64.dll", "48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 54 41 56 41 57 48 83 EC ? 41 8B E8", false, &PresentScene::oPresentScene, PresentScene::hkPresentScene);
    createHook("CreateSwapChain", "gameoverlayRenderer64.dll", "40 53 55 56 57 48 83 EC ? 48 8B F9 49 8B F1 48 8D 0D ? ? ? ? 49 8B D8 48 8B EA E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B 05 ? ? ? ? 4C 8B CE 4C 8B C3 48 8B D5 48 8B CF FF D0 8B D8 85 C0 78 ? 48 85 F6 74 ? 48 83 3E ? 74 ? 48 8B D5 48 8B CE E8 ? ? ? ? 8B C3 48 83 C4 ? 5F 5E 5D 5B C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 83 EC", false, &CreateSwapChain::oCreateSwapChain, CreateSwapChain::hkCreateSwapChain);
    createHook("ResizeBuffers", "gameoverlayRenderer64.dll", "40 53 55 56 57 41 54 41 56 41 57 48 83 EC ? 44 8B E2", false, &ResizeBuffers::oResizeBuffers, ResizeBuffers::hkResizeBuffers);

    return true;
}

void HooksManager::destroy()
{
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();

    renderer.destroy();
}

template<typename T>
inline void HooksManager::createHook(const std::string& name, const char* moduleName, const char* pattern, bool relative, T** original, void* detour)
{
    auto patternAddr = utils.memory.signatureScan(moduleName, pattern);

    if (!patternAddr)
    {
        MESSAGE_ERROR("failed to find pattern for: %s", name.c_str());
        return;
    }

    uint8_t* address = relative ? utils.memory.relativeAddress(patternAddr, 1, 5) : patternAddr;

    if (MH_CreateHook(address, reinterpret_cast<void*>(detour), reinterpret_cast<void**>(original)) != MH_OK)
    {
        MESSAGE_ERROR("failed to create hook for: %s", name.c_str());
        return;
    }

    if (MH_EnableHook(address) != MH_OK)
    {
        MESSAGE_ERROR("failed  to enable hook for: %s", name.c_str());
        return;
    }

    MESSAGE_INFO("successfully hooked: %s", name.c_str());
}
