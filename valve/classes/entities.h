#pragma once

class C_BaseHandle
{
public:
    C_BaseHandle()
        : nIndex(0xFFFFFFFF) {}

    explicit C_BaseHandle(uint32_t rawHandle)
        : nIndex(rawHandle) {}

    bool IsValid() const
    {
        return nIndex != 0xFFFFFFFF;
    }

    int GetEntryIndex() const
    {
        return nIndex & 0x7FFF;
    }

private:
    uint32_t nIndex;
};

class CEntityInstance {
public:
    CSchemaClassBinding* GetSchemaClassBinding();
};

class C_BaseEntity : public CEntityInstance
{
public:
    bool IsEntityPlayerController();
    SCHEMA("C_BaseEntity","m_iHealth", GetHealth,int)
};