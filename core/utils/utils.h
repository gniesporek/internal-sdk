#pragma once

#include <iostream>
#include <Windows.h>
#include <thread>
#include <vector>
#include <unordered_map>

enum class ConsoleColor : WORD {
    Default = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
    Info = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    Success = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
    Error = FOREGROUND_RED | FOREGROUND_INTENSITY,
    FileLine = FOREGROUND_RED | FOREGROUND_GREEN
};

#define MESSAGE(...) Utils::Console::LogToConsole(ConsoleColor::Default,"[LOG] ",__FILE__,__LINE__,__VA_ARGS__);
#define MESSAGE_INFO(...) Utils::Console::LogToConsole(ConsoleColor::Info,"[INFO] ",__FILE__,__LINE__,__VA_ARGS__);
#define MESSAGE_SUCCESS(...) Utils::Console::LogToConsole(ConsoleColor::Success,"[SUCCESS] ",__FILE__,__LINE__,__VA_ARGS__);
#define MESSAGE_ERROR(...) Utils::Console::LogToConsole(ConsoleColor::Error,"[ERROR] ",__FILE__,__LINE__,__VA_ARGS__);

#define PAD_CONCAT(a, b) a##b
#define PAD_MAKE(a, b) PAD_CONCAT(a, b)
#define PAD(size) char PAD_MAKE(pad_, __COUNTER__)[size];

class Utils {
public:
    class Console {
    public:
        static void Attach();
        static void Destroy();
        static void LogToConsole(ConsoleColor color, const char* prefix, const char* file, int line, const char* format, ...);
    private:
        static inline FILE* file = nullptr;
    };

    class SDL3 {
    public:
        static bool Setup();
        typedef int(__stdcall* fnWarpMouseInWindow)(void*, float, float y);
        static inline fnWarpMouseInWindow warpMouseInWindow = nullptr;
    };

    class Memory {
    public:
        template <typename T, typename ... U>
        T CallVMT(void* thisptr, const size_t index, U ... params)
        {
            typedef T(__thiscall* Fn)(void*, decltype(params)...);
            return (*static_cast<Fn**>(thisptr))[index](thisptr, params...);
        }
        static void* GetVMT(void* classBase, std::size_t index);
        static uint8_t* SignatureScan(const char* moduleName, const char* pattern);
        static uint8_t* RelativeAddress(uint8_t* address, std::ptrdiff_t offset, std::ptrdiff_t instructionSize);
    private:
        static std::vector<std::uint32_t> SignatureToByte(const char* pattern);
    };
};
