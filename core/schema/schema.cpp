#include "schema.h"

bool SchemaManager::Setup()
{
    std::vector<std::string> modules = { "client.dll", "engine2.dll" };

    for (auto& module : modules)
    {
        CSchemaSystemTypeScope* pSchemaTypeScope = Interfaces::pSchemaSystem->FindTypeScopeForModule(module.c_str());
        if (!pSchemaTypeScope)
        {
            MESSAGE_ERROR("failed to find schema type scope for module: %s", module);
            continue;
        }

        auto pEntries = pSchemaTypeScope->pDeclaredClasses;
        if (!pEntries)
        {
            MESSAGE_ERROR("failed to get class container for module: %s", module);
            continue;
        }

        int classesFound = 0;
        int fieldsFound = 0;

        for (int i = 0; i < pSchemaTypeScope->uNumDeclaredClasses; i++)
        {
            CSchemaDeclaredClass* pDeclaredClass = pEntries[i].pDeclaredClass;
            if (!pDeclaredClass || !pDeclaredClass->pClass)
                continue;

            CSchemaClassBinding* pClass = pDeclaredClass->pClass;
            if (!pClass->szName || pClass->uNumFields == 0)
                continue;

            classesFound++;

            for (int f = 0; f < pClass->uNumFields; f++)
            {
                CSchemaField& field = pClass->pFields[f];
                if (!field.szName)
                    continue;

                schemaData[pClass->szName][field.szName] = field.uOffset;
                fieldsFound++;
            }
        }

		MESSAGE_INFO("found %d classes and %d fields in module: %s", classesFound, fieldsFound, module.c_str());
    }

    if (schemaData.empty())
    {

        MESSAGE_ERROR("schema system setup failed: no schema data found.");
        return false;
    }

    MESSAGE_SUCCESS("schema system initialized");

    return true;
}

uint32_t SchemaManager::GetOffset(const std::string& className, const std::string& fieldName)
{
	return schemaData[className][fieldName];
}
