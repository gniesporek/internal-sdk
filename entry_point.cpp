#include "core/utils/utils.h"
#include "core/schema/schema.h"
#include "core/hooks/hooks.h"
#include "valve/interfaces/interfaces.h"

#include "valve/functions/entity_system.h"

unsigned long EntryPoint(HMODULE hModule)
{
    Utils::Console::Attach();
    Utils::SDL3::Setup();
    Interfaces::Setup();
    EntitySystem::Setup();

    SchemaManager::Setup();
    HooksManager::Setup();

    while(!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	Utils::Console::Destroy();
    HooksManager::Destroy();

    FreeLibraryAndExitThread(hModule, 0);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
    case DLL_PROCESS_ATTACH:
        auto hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)EntryPoint, hinstDLL, 0, nullptr);
        if (hThread)
            CloseHandle(hThread);
        break;
    }
    return TRUE;
}