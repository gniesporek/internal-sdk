#include "hooks.h"

bool HooksManager::Setup()
{
    if (MH_Initialize() != MH_OK) {
        MESSAGE_ERROR("failed to initialize minhook");
        return false;
    }

    CreateHook("PresentScene", "gameoverlayRenderer64.dll", "48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 54 41 56 41 57 48 83 EC ? 41 8B E8", false, &PresentScene::oPresentScene, PresentScene::hkPresentScene);
    CreateHook("CreateSwapChain", "gameoverlayRenderer64.dll", "40 53 55 56 57 48 83 EC ? 48 8B F9 49 8B F1 48 8D 0D ? ? ? ? 49 8B D8 48 8B EA E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 48 8B 05 ? ? ? ? 4C 8B CE 4C 8B C3 48 8B D5 48 8B CF FF D0 8B D8 85 C0 78 ? 48 85 F6 74 ? 48 83 3E ? 74 ? 48 8B D5 48 8B CE E8 ? ? ? ? 8B C3 48 83 C4 ? 5F 5E 5D 5B C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 83 EC", false, &CreateSwapChain::oCreateSwapChain, CreateSwapChain::hkCreateSwapChain);
    CreateHook("ResizeBuffers", "gameoverlayRenderer64.dll", "40 53 55 56 57 41 54 41 56 41 57 48 83 EC ? 44 8B E2", false, &ResizeBuffers::oResizeBuffers, ResizeBuffers::hkResizeBuffers);
    CreateHook("OnClientOutput", "engine2.dll", "4C 8B DC 49 89 5B ? 49 89 6B ? 49 89 73 ? 57 41 56 41 57 48 83 EC", false, &OnClientOutput::oOnClientOutput, OnClientOutput::hkOnClientOutput);

    CreateHook("RelativeMouseMode", "inputsystem.dll", "48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 0F B6 F2", false, &RelativeMouseMode::oSetRelativeMouseMode, RelativeMouseMode::hkSetRelativeMouseMode);
    CreateHook("MouseInput", "client.dll", "40 53 48 83 EC ? 80 B9 ? ? ? ? ? 48 8B D9 75 ? 48 8B 0D ? ? ? ? 48 8B 01", false, &MouseInput::oMouseInput, MouseInput::hkMouseInput);

    return true;
}

void HooksManager::Destroy()
{
    MH_DisableHook(MH_ALL_HOOKS);
    MH_RemoveHook(MH_ALL_HOOKS);
    MH_Uninitialize();

    Renderer::Destroy();
}

template<typename T>
inline void HooksManager::CreateHook(const std::string& name, const char* moduleName, const char* pattern, bool relative, T** original, void* detour)
{
    auto patternAddr = Utils::Memory::SignatureScan(moduleName, pattern);

    if (!patternAddr)
    {
        MESSAGE_ERROR("failed to find pattern for: %s", name.c_str());
        return;
    }

    uint8_t* address = relative ? Utils::Memory::RelativeAddress(patternAddr, 1, 5) : patternAddr;

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
