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

#define MESSAGE(...) utils.console.logToConsole(ConsoleColor::Default,"[LOG] ",__FILE__,__LINE__,__VA_ARGS__);
#define MESSAGE_INFO(...) utils.console.logToConsole(ConsoleColor::Info,"[INFO] ",__FILE__,__LINE__,__VA_ARGS__);
#define MESSAGE_SUCCESS(...) utils.console.logToConsole(ConsoleColor::Success,"[SUCCESS] ",__FILE__,__LINE__,__VA_ARGS__);
#define MESSAGE_ERROR(...) utils.console.logToConsole(ConsoleColor::Error,"[ERROR] ",__FILE__,__LINE__,__VA_ARGS__);

#define PAD_CONCAT(a, b) a##b
#define PAD_MAKE(a, b) PAD_CONCAT(a, b)
#define PAD(size) char PAD_MAKE(pad_, __COUNTER__)[size];

class Utils {
public:
    class Console {
    public:
        void attach();
        void destroy();
		void logToConsole(ConsoleColor color, const char* prefix, const char* file, int line, const char* format, ...);
    private:
        FILE* file = nullptr;
    };
    
    class SDL3 {
    public:
        bool setup();
        typedef int(__stdcall* fnWarpMouseInWindow)(void*, float, float y);
		fnWarpMouseInWindow warpMouseInWindow = nullptr;
    };
	SDL3 sdl3;

    class Memory {
    public:
        template <typename T, typename ... U>
        T callVMT(void* thisptr, const size_t index, U ... params)
        {
            typedef T(__thiscall* Fn)(void*, decltype(params)...);
            return (*static_cast<Fn**>(thisptr))[index](thisptr, params...);
        }
        void* getVMT(void* classBase, std::size_t index);
        uint8_t* signatureScan(const char* moduleName, const char* pattern);
        uint8_t* relativeAddress(uint8_t* address, std::ptrdiff_t offset, std::ptrdiff_t instructionSize);
    private:
        std::vector<std::uint32_t> signatureToByte(const char* pattern);
    };

    Console console;
    Memory memory;
};
inline Utils utils;