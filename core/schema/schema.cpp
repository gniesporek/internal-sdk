#include "schema.h"

bool SchemaManager::setup()
{
    std::vector<std::string> modules = { "client.dll", "engine2.dll" };

    for (auto& module : modules)
    {
        CSchemaSystemTypeScope* pSchemaTypeScope = interfaces.pSchemaSystem->find_type_scope_for_module(module.c_str());
        if (!pSchemaTypeScope)
        {
            MESSAGE_ERROR("failed to find schema type scope for module: ", module);
            continue;
        }

        auto pEntries = pSchemaTypeScope->pDeclaredClasses;
        if (!pEntries)
        {
            MESSAGE_ERROR("failed to get class container for module: ", module);
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

                schema_data[pClass->szName][field.szName] = field.uOffset;
                fieldsFound++;
            }
        }
    }

    if (schema_data.empty())
    {

        MESSAGE_ERROR("schema system setup failed: no schema data found.");
        return false;
    }

    MESSAGE_SUCCESS("schema system initialized");

    return true;
}

uint32_t SchemaManager::get_offset(const std::string& class_name, const std::string& field_name)
{
	return schema_data[class_name][field_name];
}
