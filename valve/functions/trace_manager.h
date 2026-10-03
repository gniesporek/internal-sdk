#pragma once
#include <array>
#include <assert.h>

#include "../classes/classes.h"

#include "hitbox_system.h"

#include "../globals.h"

enum BuiltInInteractionLayer_t
{
	LAYER_INDEX_CONTENTS_SOLID = 0,
	LAYER_INDEX_CONTENTS_HITBOX,
	LAYER_INDEX_CONTENTS_TRIGGER,
	LAYER_INDEX_CONTENTS_SKY,
	LAYER_INDEX_FIRST_USER,
	LAYER_INDEX_NOT_FOUND = -1,
	LAYER_INDEX_MAX_ALLOWED = 64,
};

enum StandardInteractionLayers_t
{
	LAYER_INDEX_CONTENTS_PLAYER_CLIP = LAYER_INDEX_FIRST_USER,
	LAYER_INDEX_CONTENTS_NPC_CLIP,
	LAYER_INDEX_CONTENTS_BLOCK_LOS,
	LAYER_INDEX_CONTENTS_BLOCK_LIGHT,
	LAYER_INDEX_CONTENTS_LADDER,
	LAYER_INDEX_CONTENTS_PICKUP,
	LAYER_INDEX_CONTENTS_BLOCK_SOUND,
	LAYER_INDEX_CONTENTS_NODRAW,
	LAYER_INDEX_CONTENTS_WINDOW,
	LAYER_INDEX_CONTENTS_PASS_BULLETS,
	LAYER_INDEX_CONTENTS_WORLD_GEOMETRY,
	LAYER_INDEX_CONTENTS_WATER,
	LAYER_INDEX_CONTENTS_SLIME,
	LAYER_INDEX_CONTENTS_TOUCH_ALL,
	LAYER_INDEX_CONTENTS_PLAYER,
	LAYER_INDEX_CONTENTS_NPC,
	LAYER_INDEX_CONTENTS_DEBRIS,
	LAYER_INDEX_CONTENTS_PHYSICS_PROP,
	LAYER_INDEX_CONTENTS_NAV_IGNORE,
	LAYER_INDEX_CONTENTS_NAV_LOCAL_IGNORE,
	LAYER_INDEX_CONTENTS_POST_PROCESSING_VOLUME,
	LAYER_INDEX_CONTENTS_UNUSED_LAYER3,
	LAYER_INDEX_CONTENTS_CARRIED_OBJECT,
	LAYER_INDEX_CONTENTS_PUSHAWAY,
	LAYER_INDEX_CONTENTS_SERVER_ENTITY_ON_CLIENT,
	LAYER_INDEX_CONTENTS_CARRIED_WEAPON,
	LAYER_INDEX_CONTENTS_STATIC_LEVEL,
	LAYER_INDEX_FIRST_MOD_SPECIFIC,
};

enum ModSpecificInteractionLayers_t
{
	LAYER_INDEX_CONTENTS_CSGO_TEAM1 = LAYER_INDEX_FIRST_MOD_SPECIFIC,
	LAYER_INDEX_CONTENTS_CSGO_TEAM2,
	LAYER_INDEX_CONTENTS_CSGO_GRENADE_CLIP,
	LAYER_INDEX_CONTENTS_CSGO_DRONE_CLIP,
	LAYER_INDEX_CONTENTS_CSGO_MOVEABLE,
	LAYER_INDEX_CONTENTS_CSGO_OPAQUE,
	LAYER_INDEX_CONTENTS_CSGO_MONSTER,
	LAYER_INDEX_CONTENTS_CSGO_UNUSED_LAYER,
	LAYER_INDEX_CONTENTS_CSGO_THROWN_GRENADE,
};

enum BuiltInCollisionGroup_t
{
	COLLISION_GROUP_ALWAYS = 0,
	COLLISION_GROUP_NONPHYSICAL,
	COLLISION_GROUP_TRIGGER,
	COLLISION_GROUP_CONDITIONALLY_SOLID,
	COLLISION_GROUP_FIRST_USER,
	COLLISION_GROUPS_MAX_ALLOWED = 64,
};

enum StandardCollisionGroups_t
{
	COLLISION_GROUP_DEFAULT = COLLISION_GROUP_FIRST_USER,
	COLLISION_GROUP_DEBRIS,
	COLLISION_GROUP_INTERACTIVE_DEBRIS,
	COLLISION_GROUP_INTERACTIVE,
	COLLISION_GROUP_PLAYER,
	COLLISION_GROUP_BREAKABLE_GLASS,
	COLLISION_GROUP_VEHICLE,
	COLLISION_GROUP_PLAYER_MOVEMENT,
	COLLISION_GROUP_NPC,
	COLLISION_GROUP_IN_VEHICLE,
	COLLISION_GROUP_WEAPON,
	COLLISION_GROUP_VEHICLE_CLIP,
	COLLISION_GROUP_PROJECTILE,
	COLLISION_GROUP_DOOR_BLOCKER,
	COLLISION_GROUP_PASSABLE_DOOR,
	COLLISION_GROUP_DISSOLVING,
	COLLISION_GROUP_PUSHAWAY,
	COLLISION_GROUP_NPC_ACTOR,
	COLLISION_GROUP_NPC_SCRIPTED,
	COLLISION_GROUP_PZ_CLIP,
	COLLISION_GROUP_PROPS,
	LAST_SHARED_COLLISION_GROUP,
};

#define	CONTENTS_EMPTY						0ull

#define CONTENTS_SOLID						( 1ull << LAYER_INDEX_CONTENTS_SOLID )
#define CONTENTS_HITBOX						( 1ull << LAYER_INDEX_CONTENTS_HITBOX )
#define CONTENTS_TRIGGER					( 1ull << LAYER_INDEX_CONTENTS_TRIGGER )
#define CONTENTS_SKY						( 1ull << LAYER_INDEX_CONTENTS_SKY )

#define CONTENTS_PLAYER_CLIP				( 1ull << LAYER_INDEX_CONTENTS_PLAYER_CLIP )
#define CONTENTS_NPC_CLIP					( 1ull << LAYER_INDEX_CONTENTS_NPC_CLIP )
#define CONTENTS_BLOCK_LOS					( 1ull << LAYER_INDEX_CONTENTS_BLOCK_LOS )
#define CONTENTS_BLOCK_LIGHT				( 1ull << LAYER_INDEX_CONTENTS_BLOCK_LIGHT )
#define CONTENTS_LADDER						( 1ull << LAYER_INDEX_CONTENTS_LADDER )
#define CONTENTS_PICKUP						( 1ull << LAYER_INDEX_CONTENTS_PICKUP )
#define CONTENTS_BLOCK_SOUND				( 1ull << LAYER_INDEX_CONTENTS_BLOCK_SOUND )
#define CONTENTS_NODRAW						( 1ull << LAYER_INDEX_CONTENTS_NODRAW )
#define CONTENTS_WINDOW						( 1ull << LAYER_INDEX_CONTENTS_WINDOW )
#define CONTENTS_PASS_BULLETS				( 1ull << LAYER_INDEX_CONTENTS_PASS_BULLETS )
#define CONTENTS_WORLD_GEOMETRY				( 1ull << LAYER_INDEX_CONTENTS_WORLD_GEOMETRY )
#define CONTENTS_WATER						( 1ull << LAYER_INDEX_CONTENTS_WATER )
#define CONTENTS_SLIME						( 1ull << LAYER_INDEX_CONTENTS_SLIME )
#define CONTENTS_TOUCH_ALL					( 1ull << LAYER_INDEX_CONTENTS_TOUCH_ALL )
#define CONTENTS_PLAYER						( 1ull << LAYER_INDEX_CONTENTS_PLAYER )
#define CONTENTS_NPC						( 1ull << LAYER_INDEX_CONTENTS_NPC )
#define CONTENTS_DEBRIS						( 1ull << LAYER_INDEX_CONTENTS_DEBRIS )
#define CONTENTS_PHYSICS_PROP				( 1ull << LAYER_INDEX_CONTENTS_PHYSICS_PROP )
#define CONTENTS_NAV_IGNORE					( 1ull << LAYER_INDEX_CONTENTS_NAV_IGNORE )
#define CONTENTS_NAV_LOCAL_IGNORE			( 1ull << LAYER_INDEX_CONTENTS_NAV_LOCAL_IGNORE )
#define CONTENTS_POST_PROCESSING_VOLUME		( 1ull << LAYER_INDEX_CONTENTS_POST_PROCESSING_VOLUME )
#define CONTENTS_UNUSED_LAYER3				( 1ull << LAYER_INDEX_CONTENTS_UNUSED_LAYER3 )
#define CONTENTS_CARRIED_OBJECT				( 1ull << LAYER_INDEX_CONTENTS_CARRIED_OBJECT )
#define CONTENTS_PUSHAWAY					( 1ull << LAYER_INDEX_CONTENTS_PUSHAWAY )
#define CONTENTS_SERVER_ENTITY_ON_CLIENT	( 1ull << LAYER_INDEX_CONTENTS_SERVER_ENTITY_ON_CLIENT )
#define CONTENTS_CARRIED_WEAPON				( 1ull << LAYER_INDEX_CONTENTS_CARRIED_WEAPON )
#define CONTENTS_STATIC_LEVEL				( 1ull << LAYER_INDEX_CONTENTS_STATIC_LEVEL )

#define CONTENTS_CSGO_TEAM1					( 1ull << LAYER_INDEX_CONTENTS_CSGO_TEAM1 )
#define CONTENTS_CSGO_TEAM2					( 1ull << LAYER_INDEX_CONTENTS_CSGO_TEAM2 )
#define CONTENTS_CSGO_GRENADE_CLIP			( 1ull << LAYER_INDEX_CONTENTS_CSGO_GRENADE_CLIP )
#define CONTENTS_CSGO_DRONE_CLIP			( 1ull << LAYER_INDEX_CONTENTS_CSGO_DRONE_CLIP )
#define CONTENTS_CSGO_MOVEABLE				( 1ull << LAYER_INDEX_CONTENTS_CSGO_MOVEABLE )
#define CONTENTS_CSGO_OPAQUE				( 1ull << LAYER_INDEX_CONTENTS_CSGO_OPAQUE )
#define CONTENTS_CSGO_MONSTER				( 1ull << LAYER_INDEX_CONTENTS_CSGO_MONSTER )
#define CONTENTS_CSGO_UNUSED_LAYER			( 1ull << LAYER_INDEX_CONTENTS_CSGO_UNUSED_LAYER )
#define CONTENTS_CSGO_THROWN_GRENADE		( 1ull << LAYER_INDEX_CONTENTS_CSGO_THROWN_GRENADE )

#define	MASK_ALL					(~0ull)
#define	MASK_SOLID					(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_PLAYER|CONTENTS_NPC|CONTENTS_PASS_BULLETS)
#define	MASK_PLAYERSOLID			(CONTENTS_SOLID|CONTENTS_PLAYER_CLIP|CONTENTS_WINDOW|CONTENTS_PLAYER|CONTENTS_NPC|CONTENTS_PASS_BULLETS)
#define	MASK_NPCSOLID				(CONTENTS_SOLID|CONTENTS_NPC_CLIP|CONTENTS_WINDOW|CONTENTS_PLAYER|CONTENTS_NPC|CONTENTS_PASS_BULLETS)
#define	MASK_NPCFLUID				(CONTENTS_SOLID|CONTENTS_NPC_CLIP|CONTENTS_WINDOW|CONTENTS_PLAYER|CONTENTS_NPC)
#define	MASK_WATER					(CONTENTS_WATER|CONTENTS_SLIME)
#define	MASK_SHOT					(CONTENTS_SOLID|CONTENTS_PLAYER|CONTENTS_NPC|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_HITBOX)
#define MASK_SHOT_BRUSHONLY			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_DEBRIS)
#define MASK_SHOT_HULL				(CONTENTS_SOLID|CONTENTS_PLAYER|CONTENTS_NPC|CONTENTS_WINDOW|CONTENTS_DEBRIS|CONTENTS_PASS_BULLETS)
#define MASK_SHOT_PORTAL			(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_PLAYER|CONTENTS_NPC)
#define MASK_SOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_PASS_BULLETS)
#define MASK_PLAYERSOLID_BRUSHONLY	(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_PLAYER_CLIP|CONTENTS_PASS_BULLETS)
#define MASK_NPCSOLID_BRUSHONLY		(CONTENTS_SOLID|CONTENTS_WINDOW|CONTENTS_NPC_CLIP|CONTENTS_PASS_BULLETS)

#define MASK_CLIP_TO_PLAYER (CONTENTS_PLAYER | CONTENTS_HITBOX )
#define MASK_PLAYER_VISIBLE (CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_PLAYER | CONTENTS_NPC | CONTENTS_DEBRIS | CONTENTS_HITBOX | CONTENTS_BLOCK_LOS)


class CUpdateValue {
public:
	float PreviousLengthMod{};     
	float CurrentLengthMod{};     
	PAD(0xA);                      
	short HandleIndex{};          
	PAD(0x4);                      
};

class CTraceArrElement {
public:
	PAD(0x38);                     
};

class CTraceData {
public:
	std::int32_t NumElements{};                    
	float Unk0_{ 52.f };                            
	CTraceArrElement* ElementsPointer{};            
	std::int32_t NumLocalElements{ 0x80 };          
	std::uint32_t Unk1_{ 0x80000000u };            
	std::array<CTraceArrElement, 0x80> Elements{};  
	PAD(0x8);                                       
	std::int64_t NumUpdateValues{};                 
	CUpdateValue* UpdateValuesPointer{};            
	PAD(0xC8);                                     
	Vector3D Start{}, End{};                        
	float Scale{ 1.f };
	std::int32_t Uk5{};
	PAD(0x48);

	auto UpdateValuesSize() const noexcept
	{
		return NumUpdateValues;
	}

	template <std::integral T>
	auto& UpdateValue(T i) const noexcept
	{
		assert(static_cast<std::size_t>(i) <
			static_cast<std::size_t>(UpdateValuesSize()));

		return UpdateValuesPointer[i];
	}

	auto ElementsSize() const noexcept
	{
		return NumElements;
	}

	template <std::integral T>
	auto& Element(T i) const noexcept
	{
		assert(static_cast<std::size_t>(i) <
			static_cast<std::size_t>(ElementsSize()));

		return ElementsPointer[i];
	}
};
static_assert(sizeof(CTraceData) >= 0x1914);

class SurfaceData
{
public:
	PAD(0x8);
	float PenetrationDataModifier{};
	float DamagerModifier{};
	PAD(0x4);
	int Material{};
};

class CGameTrace {
public:
    bool DidHit() const
    {
        return Fraction < 1.f;
    }

    void* Surface; // 0x00
    C_BaseEntity* Entity; // 0x08
    CHitbox* Hitbox; // 0x10
    PAD(0x38);
    uint64_t Contents{};
    PAD(0x20); // -0x4
    Vector3D Start{};
    Vector3D End{};
    Vector3D Normal{};
    Vector3D Position{};
    PAD(0x4);
    float Fraction{};
    PAD(0x6);
    bool AllSolid{};
    PAD(0x4D); // -0x10 later
};
static_assert(sizeof(CGameTrace) == 0x108);

class CRay {
public:
	Vector3D Start;
	Vector3D End;
	Vector3D Mins;
	Vector3D Maxs;
private:
	PAD(0x4);
public:
	uint8_t  Type;
};
static_assert(sizeof(CRay) == 0x38);


class CTraceFilter {
public:
    CTraceFilter(C_CSPlayerPawn* pPawn, std::uint64_t mask, int num, uint16_t unk);
private:
    PAD(0x48);
};
static_assert(sizeof(CTraceFilter) == 0x48);

class TraceManager {
public:

	static void CreateTrace(CTraceData* pTraceData, Vector3D startPosition, Vector3D endPosition, CTraceFilter* pTraceFilter, int PenetrationCount);
	static void InitGameTrace(CGameTrace* pTrace);
	static void GetTraceInformation(CTraceData* pTraceData, CGameTrace* pGameTrace, float unkown, void* array);
	static C_BaseEntity* TraceLine(Vector3D startPosition, Vector3D endPosition, C_CSPlayerPawn* target);
    static bool TraceShape(Vector3D startPosition, Vector3D endPosition, CRay* pRay, CTraceFilter* pTraceFilter, CGameTrace* pTrace);
};

class PenetrationData {
public:
	float Damage; 
	int Hitbox; 
	bool Penetrated = true; 
	int PenetrationCount = 0;
};

class HandleBulletPenetrationData {
public:
	float Damage{};
	float Penetration{};
	float RangeModifier{};
	float Range{};
	int Count{};
	bool Failed{};
	HandleBulletPenetrationData(float damage, float penetration, float rangeModifier, float range, int count, bool failed) :
		Damage(damage), Penetration(penetration), RangeModifier(rangeModifier), Range(range), Count(count), Failed(failed) {}
};

class PenetrationSystem
{
public:
	static inline void ScaleDamage(const int HitGroup, C_CSPlayerPawn* pPawn, const float WeaponArmorRatio, const float HeadshotMultiplier, float* DamageToScale);
	static bool SimulateFireBullet(Vector3D vecStartPos, Vector3D vecEndPos, C_CSPlayerPawn* pTarget, C_CSWeapon* pCurrentWeapon, PenetrationData& penetrationData);
	static float GetDamage(Vector3D vecStartPos, Vector3D vecEndPos, C_CSPlayerPawn* pTarget, C_CSWeapon* pCurrentWeapon);
private:
	static inline bool HandleBulletPenetration(CTraceData* traceData, HandleBulletPenetrationData* bulletData, CUpdateValue* modValues, int playerTeam);
};