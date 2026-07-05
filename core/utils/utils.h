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

#define MESSAGE(...) utils.console.log_to_console(ConsoleColor::Default,"[LOG] ",__FILE__,__LINE__,__VA_ARGS__);
#define MESSAGE_INFO(...) utils.console.log_to_console(ConsoleColor::Info,"[INFO] ",__FILE__,__LINE__,__VA_ARGS__);
#define MESSAGE_SUCCESS(...) utils.console.log_to_console(ConsoleColor::Success,"[SUCCESS] ",__FILE__,__LINE__,__VA_ARGS__);
#define MESSAGE_ERROR(...) utils.console.log_to_console(ConsoleColor::Error,"[ERROR] ",__FILE__,__LINE__,__VA_ARGS__);

#define PAD_CONCAT(a, b) a##b
#define PAD_MAKE(a, b) PAD_CONCAT(a, b)
#define PAD(size) char PAD_MAKE(pad_, __COUNTER__)[size];

class Utils {
public:
    class Console {
    public:
        void attach();
        void destroy();
		void log_to_console(ConsoleColor color, const char* prefix, const char* file, int line, const char* format, ...);
    private:
        FILE* file = nullptr;
    };


    class Memory {
    public:
        template <typename T, typename ... U>
        T call_virtual_function(void* thisptr, const size_t index, U ... params)
        {
            typedef T(__thiscall* Fn)(void*, decltype(params)...);
            return (*static_cast<Fn**>(thisptr))[index](thisptr, params...);
        }
        void* get_virtual_function(void* class_base, std::size_t index);
        uint8_t* signature_scan(const char* moduleName, const char* pattern);
        uint8_t* relative_address(uint8_t* address, std::ptrdiff_t offset, std::ptrdiff_t instruction_size);
    private:
        std::vector<std::uint32_t> signature_to_byte(const char* pattern);
    };

    Console console;
    Memory memory;
};
inline Utils utils;