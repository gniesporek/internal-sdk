#include "core/utils/utils.h"

unsigned long EntryPoint(HMODULE hModule)
{
    utils.console.attach();

    while(!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

	utils.console.destroy();

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