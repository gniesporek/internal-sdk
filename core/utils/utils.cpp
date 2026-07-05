#include "utils.h"

void Utils::Console::attach()
{
    AllocConsole();
    freopen_s(&file, "CONOUT$", "w", stdout);
    SetConsoleTitleA("command line");
}
void Utils::Console::destroy()
{
    if (file)
    {
        fclose(file);
        file = nullptr;
    }

    FreeConsole();
}