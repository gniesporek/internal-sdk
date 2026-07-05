#pragma once

class CSchemaField {
public:
    const char* szName;           // 0x00
    void* pType;                  // 0x08
    std::uint32_t uOffset;        // 0x10
    std::uint32_t uMetadataSize;  // 0x14
    void* pMetadata;              // 0x18
};

class CSchemaClassBinding
{
public:
    PAD(0x8);                 // 0x00
    const char* szName;         // 0x08
    const char* szModuleName;   // 0x10
    std::uint32_t uSize;        // 0x18
    PAD(0x8);
    std::uint16_t uNumFields;   // 0x24 
    PAD(0x2);
    std::uint16_t uStaticSize;
    std::uint16_t uMetadataSize;
    PAD(0x4);
    CSchemaField* pFields;      // 0x30 
};

class CSchemaDeclaredClass {
public:
    PAD(0x8);                // 0x00 (VTable)
    const char* szName;           // 0x08
    const char* szModuleName;     // 0x10
    const char* szUnknownStr;     // 0x18
    CSchemaClassBinding* pClass;         // 0x20
};

class CSchemaDeclaredClassEntry {
public:
    std::uint64_t nHash[2];       // 0x00
    CSchemaDeclaredClass* pDeclaredClass; // 0x10
};

class CSchemaSystemTypeScope {
public:
    PAD(0x8);                // 0x00
    char szName[256];             // 0x08
    PAD(0x368);              // 0x108
    std::uint16_t uNumDeclaredClasses; // 0x470
    PAD(0x6);                // 0x472
    CSchemaDeclaredClassEntry* pDeclaredClasses; // 0x478
};

// "SchemaSystem_001"
class ISchemaSystem
{
public:
    CSchemaSystemTypeScope* FindTypeScopeForModule(const char* module)
    {
        typedef CSchemaSystemTypeScope* (__thiscall* fnFindTypeScopeForModule)(void*, const char*, void*);
        static auto FindTypeScopeForModuleFn = (fnFindTypeScopeForModule)(Utils::Memory::SignatureScan("schemasystem.dll", "48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 48 8B DA"));
        return FindTypeScopeForModuleFn(this, module, nullptr);
    }
    CSchemaSystemTypeScope* GlobalTypeScope()
    {
        typedef CSchemaSystemTypeScope* (__thiscall* fnGlobalTypeScope)(void*);
        static auto GlobalTypeScopeFn = (fnGlobalTypeScope)(Utils::Memory::SignatureScan("schemasystem.dll", "48 8D 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56"));
        return GlobalTypeScopeFn(this);
    }
};