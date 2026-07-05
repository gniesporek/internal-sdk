#pragma once
#include "../utils/utils.h"

#include "../../valve/interfaces/interfaces.h" 

#define SCHEMA(className, fieldName, varName, type) \
type& varName() { \
    static uint32_t offset = CSchemaSystem::GetOffset(className, fieldName); \
    return *reinterpret_cast<type*>((uintptr_t)this + offset); \
}

class SchemaManager
{
public:
    bool setup();
    uint32_t get_offset(const std::string& class_name, const std::string& field_name);
private:
    static inline std::unordered_map<std::string, std::unordered_map<std::string, uint32_t>> schema_data;
};
inline SchemaManager schema_manager;