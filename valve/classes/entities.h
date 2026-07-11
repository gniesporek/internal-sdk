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

class C_BaseEntity 
{
public:
    bool IsEntityPlayerController();
};