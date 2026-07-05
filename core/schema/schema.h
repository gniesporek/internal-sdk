#pragma once
#include "../utils/utils.h"

#include "../../valve/interfaces/interfaces.h" 

#define SCHEMA(className, fieldName, varName, type) \
type& varName() { \
    static uint32_t offset = SchemaManager::GetOffset(className, fieldName); \
    return *reinterpret_cast<type*>((uintptr_t)this + offset); \
}

class SchemaManager
{
public:
    static bool Setup();
    static uint32_t GetOffset(const std::string& className, const std::string& fieldName);
private:
    static inline std::unordered_map<std::string, std::unordered_map<std::string, uint32_t>> schemaData;
};