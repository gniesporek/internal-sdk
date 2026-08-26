#include "hitbox_system.h"

CHitbox* HitboxSystem::GetHitbox(C_CSPlayerPawn* Player, int hitboxIndex)
{
    if (!Player || !Player->IsEntityPlayer() || Player == Globals::LocalPlayerPawn)
        return nullptr;

    CHitboxSet* hitboxSet = Player->GetHitboxSet();
    if (!hitboxSet)
        return nullptr;

    CUtlVector<CHitbox>& hitboxes = hitboxSet->Hitboxes;
    if (hitboxIndex < 0 || hitboxIndex >= hitboxes.size)
        return nullptr;

    return hitboxes.atPtr(hitboxIndex);
}

Vector3D HitboxSystem::GetHitboxPosition(C_CSPlayerPawn* Player, int hitboxIndex)
{
    if (!Player)
        return Vector3D();

    CHitboxSet* set = Player->GetHitboxSet();
    if (!set)
        return Vector3D();

    auto hitbox = GetHitbox(Player, hitboxIndex);
    if (!hitbox)
        return Vector3D();

    Transform_t transforms[HITBOX_MAX];

    if (!Player->HitboxToWorldTransform(set, transforms))
        return Vector3D();

    auto& matrix = transforms[hitboxIndex];

    Vector3D mins = hitbox->Mins - Vector3D(hitbox->Radius, hitbox->Radius, hitbox->Radius);
    Vector3D maxs = hitbox->Maxs + Vector3D(hitbox->Radius, hitbox->Radius, hitbox->Radius);

    Vector3D worldMin, worldMax;

    Math::VectorTransform(mins, matrix.ToMatrix3x4(), worldMin);
    Math::VectorTransform(maxs, matrix.ToMatrix3x4(), worldMax);

    return (worldMin + worldMax) * 0.5f;
}
