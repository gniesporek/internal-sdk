#pragma once

#include <iostream>
#include <Windows.h>
#include <thread>

class Utils {
public:
    class Console {
    public:
        void attach();
        void destroy();
    private:
        FILE* file = nullptr;
    };

    Console console;
};

inline Utils utils;