#pragma once


class CCSGOInput {
public:
    bool IsInThirdPerson() {
        static const auto offset = *(uint32_t*)(Utils::Memory::SignatureScan("client.dll", "41 C6 80 ? ? ? ? ? F3 41 0F 11 80") + 3);
        return  *(bool*)((this) + offset);
    }

    void SetThirdPerson(bool value) {
        static const auto offset = *(uint32_t*)(Utils::Memory::SignatureScan("client.dll", "41 C6 80 ? ? ? ? ? F3 41 0F 11 80") + 3);
        *(bool*)((this) + offset) = value ? 1 : 0;
    }

    void SetViewAngles(Vector3D& angles) {
        typedef void(__fastcall* fnSetViewAngles)(CCSGOInput*, int, Vector3D&);
        static auto SetViewAngles = (fnSetViewAngles)(Utils::Memory::SignatureScan("client.dll", "85 D2 75 ? 48 63 81"));
        if (SetViewAngles)
            SetViewAngles(this, 0, std::ref(angles));
    }

    Vector3D* GetViewAngles()
    {
        typedef Vector3D* (__fastcall* fnGetViewAngles)(CCSGOInput*, int);
        static auto GetViewAngles = (fnGetViewAngles)(Utils::Memory::SignatureScan("client.dll", "4C 8B C1 85 D2 74 ? 48 8D 05"));
        return GetViewAngles(this, 0);
    }

    static inline bool ToggleThirdPerson = false;
};