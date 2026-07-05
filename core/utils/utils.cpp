#include "utils.h"

void Utils::Console::attach()
{
    AllocConsole();
    freopen_s(&file, "CONOUT$", "w", stdout);
    SetConsoleTitleA("command line");

	MESSAGE_SUCCESS("console attached");
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


void Utils::Console::log_to_console(ConsoleColor color, const char* prefix, const char* file, int line, const char* format, ...)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, (WORD)color);

	std::cout << prefix;

	SetConsoleTextAttribute(hConsole, (WORD)ConsoleColor::Default);

	char buffer[1024];

	va_list args;
	va_start(args, format);
	vsnprintf_s(buffer, sizeof(buffer), _TRUNCATE, format, args);
	va_end(args);

	std::cout << buffer;

	const char* filename = strrchr(file, '\\');
	if (!filename) filename = strrchr(file, '/');
	filename = filename ? filename + 1 : file;

	SetConsoleTextAttribute(hConsole, (WORD)ConsoleColor::FileLine);
	std::cout << " (" << filename << ":" << line << ")";

	SetConsoleTextAttribute(hConsole, (WORD)ConsoleColor::Default);
	std::cout << std::endl;
}

void* Utils::Memory::get_virtual_function(void* class_base, std::size_t index)
{
	void** vtable = *reinterpret_cast<void***>(class_base);
	return vtable[index];
}

uint8_t* Utils::Memory::signature_scan(const char* moduleName, const char* pattern)
{
	HMODULE module_handle = GetModuleHandle(moduleName);

	if (!module_handle)
	{
		return nullptr;
	}

	PIMAGE_DOS_HEADER dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module_handle);
	PIMAGE_NT_HEADERS nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uint8_t*>(module_handle) + dos_header->e_lfanew);

	std::size_t size_of_image = nt_headers->OptionalHeader.SizeOfImage;
	std::vector<std::uint32_t> pattern_bytes = signature_to_byte(pattern);
	std::uint8_t* image_base = reinterpret_cast<std::uint8_t*>(module_handle);

	std::size_t pattern_size = pattern_bytes.size();
	std::uint32_t* array_of_bytes = pattern_bytes.data();

	for (std::size_t i = 0; i < size_of_image - pattern_size; i++)
	{
		bool found = true;

		for (std::size_t j = 0; j < pattern_size; j++)
		{
			if (image_base[i + j] != array_of_bytes[j] && array_of_bytes[j] != -1)
			{
				found = false;
				break;
			}
		}

		if (found)
		{
			return &image_base[i];
		}
	}

	return nullptr;
}

uint8_t* Utils::Memory::relative_address(uint8_t* address, std::ptrdiff_t offset, std::ptrdiff_t instruction_size)
{
	if (!address)
		return nullptr;

	int32_t rel = *reinterpret_cast<int32_t*>(address + offset);

	uintptr_t rip = reinterpret_cast<uintptr_t>(address) + instruction_size;

	return reinterpret_cast<uint8_t*>(rip + rel);
}

std::vector<std::uint32_t>  Utils::Memory::signature_to_byte(const char* pattern)
{
	std::vector<std::uint32_t> bytes;
	char* start = const_cast<char*>(pattern);
	char* end = const_cast<char*>(pattern) + std::strlen(pattern);

	for (char* current = start; current < end; current++)
	{
		if (*current == '?')
		{
			current++;

			if (*current == '?')
			{
				current++;
			}

			bytes.push_back(-1);
		}
		else
		{
			bytes.push_back(std::strtoul(current, &current, 16));
		}
	}

	return bytes;
}
