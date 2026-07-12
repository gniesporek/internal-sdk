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

bool Math::CalculateBoundingBox(C_BaseEntity* pEntity, BoundingBox& bbox, bool compute = false)
{
    Vector3D mins, maxs;

    // source 2 uses weird calcs for players/entities at map for player we do not use compute for rest we use
    if (compute) {
        if (!pEntity->ComputeHitboxSurroundingBox(&mins, &maxs))
            return false;
    }
    else {
        mins = pEntity->GetCollisionProperty()->GetMins() + pEntity->GetSceneNode()->GetAbsOrigin();
        maxs = pEntity->GetCollisionProperty()->GetMaxs() + pEntity->GetSceneNode()->GetAbsOrigin();
    }

    // basic 8 points math from source 1 nothing else
    Vector3D worldPoints[8] = 
    {
         {mins.x, mins.y, mins.z}, {mins.x, maxs.y, mins.z}, {maxs.x, maxs.y, mins.z}, {maxs.x, mins.y, mins.z},
         {maxs.x, maxs.y, maxs.z}, {mins.x, maxs.y, maxs.z}, {mins.x, mins.y, maxs.z}, {maxs.x, mins.y, maxs.z}
    };

    Vector2D screenPoints[8];

    for (int i = 0; i < 8; ++i)
        if (!WorldToScreen(worldPoints[i], screenPoints[i]))
            return false;

    int left = screenPoints[0].x, right = left;
    int top = screenPoints[0].y, bottom = top;

    for (int i = 1; i < 8; ++i) {
        left = min(left, screenPoints[i].x);
        top = min(top, screenPoints[i].y);
        right = max(right, screenPoints[i].x);
        bottom = max(bottom, screenPoints[i].y);
    }

    bbox.x = left;
    bbox.y = top;
    bbox.w = right - left;
    bbox.h = bottom - top;

    return true;
}
