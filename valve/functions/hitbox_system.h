#pragma once

#include "../classes/classes.h"

#include "../globals.h"

enum EHitGroups_t : std::uint32_t
{
	HITGROUP_INVALID = -1,
	HITGROUP_GENERIC = 0,
	HITGROUP_HEAD = 1,
	HITGROUP_CHEST = 2,
	HITGROUP_STOMACH = 3,
	HITGROUP_LEFTARM = 4,
	HITGROUP_RIGHTARM = 5,
	HITGROUP_LEFTLEG = 6,
	HITGROUP_RIGHTLEG = 7,
	HITGROUP_NECK = 8,
	HITGROUP_UNUSED = 9,
	HITGROUP_GEAR = 10,
	HITGROUP_SPECIAL = 11,
	HITGROUP_COUNT = 12,
};

enum Hitboxes_t : int
{
	HITBOX_INVALID = -1,
	HITBOX_HEAD = 0,
	HITBOX_NECK = 1,
	HITBOX_PELVIS = 2,
	HITBOX_STOMACH = 3,
	HITBOX_THORAX = 4,
	HITBOX_CHEST = 5,
	HITBOX_UPPER_CHEST = 6,
	HITBOX_LEFT_THIGH = 7,
	HITBOX_RIGHT_THIGH = 8,
	HITBOX_LEFT_CALF = 9,
	HITBOX_RIGHT_CALF = 10,
	HITBOX_LEFT_FOOT = 11,
	HITBOX_RIGHT_FOOT = 12,
	HITBOX_LEFT_HAND = 13,
	HITBOX_RIGHT_HAND = 14,
	HITBOX_LEFT_UPPER_ARM = 15,
	HITBOX_LEFT_FOREARM = 16,
	HITBOX_RIGHT_UPPER_ARM = 17,
	HITBOX_RIGHT_FOREARM = 18,
	HITBOX_MAX
};

class CHitbox {
public:
	const char* HitboxName; // 0x0
	void* Surface; // 0x8
	const char* BoneName; // 0x10
	Vector3D Mins; // 0x18
	Vector3D Maxs; // 0x24
	float Radius; // 0x30  
	uint32_t BoneNameHash; // 0x34
	int GroupID; // 0x38
	uint8_t ShapeType; // 0x3C
	bool TranslationOnly; // 0x3D
	uint32_t CRC; // 0x40
	float Color; // 0x44
	uint16_t HitboxIndex; // 0x48
	PAD(0x20);
};
static_assert(sizeof(CHitbox) == 0x70);

class CHitboxSet {
public:
	const char* HitboxSetName; // 0x0
	uint32_t HitboxesSetNameHash; // 0x8
	CUtlVector<CHitbox> Hitboxes; // 0x10
	const char* SourceFileName; // 0x28
};

class HitboxSystem {
public:
	static CHitbox* GetHitbox(C_CSPlayerPawn* Player, int hitboxIndex);
	static Vector3D GetHitboxPosition(C_CSPlayerPawn* Player, int hitboxIndex);
};