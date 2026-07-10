#include "math.h"

#include "../../core/utils/utils.h"
#include "../../ext/imgui/imgui.h"

int Math::CalculateSegments(float radius)
{
    int segments = static_cast<int>(radius * 2); 

    const int minSegments = 16;

    const int maxSegments = 128; // max 128 dla performance

    if (segments < minSegments) segments = minSegments; 
    if (segments > maxSegments) segments = maxSegments;

    return segments;
}

bool Math::WorldToScreen(const Vector3D& worldPos, Vector2D& screenPos)
{
    static float(*ViewMatrix)[4][4] = reinterpret_cast<float(*)[4][4]>(Utils::Memory::RelativeAddress(Utils::Memory::SignatureScan("client.dll", "48 8D 0D ? ? ? ? 48 89 44 24 ? 48 89 4C 24 ? 4C 8D 0D"), 3, 7));

    if (!ViewMatrix)
        return false;

    const float w = (*ViewMatrix)[3][0] * worldPos.x + (*ViewMatrix)[3][1] * worldPos.y + (*ViewMatrix)[3][2] * worldPos.z + (*ViewMatrix)[3][3];
    if (w < 0.001f)
        return false;

    screenPos.x = ImGui::GetIO().DisplaySize.x * 0.5f;
    screenPos.y = ImGui::GetIO().DisplaySize.y * 0.5f;

    screenPos.x *= 1.0f + (((*ViewMatrix)[0][0] * worldPos.x + (*ViewMatrix)[0][1] * worldPos.y + (*ViewMatrix)[0][2] * worldPos.z + (*ViewMatrix)[0][3])) / w;
    screenPos.y *= 1.0f - (((*ViewMatrix)[1][0] * worldPos.x + (*ViewMatrix)[1][1] * worldPos.y + (*ViewMatrix)[1][2] * worldPos.z + (*ViewMatrix)[1][3])) / w;

    return true;
}
