#include "trace_manager.h"

CTraceFilter::CTraceFilter(C_CSPlayerPawn* pPawn, std::uint64_t mask, int num, uint16_t unk)
{
	typedef CTraceFilter* (__fastcall* oCGameTraceConstructor)(void*, C_CSPlayerPawn*, std::uint64_t, int, uint16_t);
	static oCGameTraceConstructor GameTraceConstructor = (oCGameTraceConstructor)(Utils::Memory::SignatureScan("client.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 0F B6 41 ? 33 FF 24"));

	if (!GameTraceConstructor)
		return;

	GameTraceConstructor(this, pPawn, mask, num, unk);
}

void TraceManager::CreateTrace(CTraceData* pTraceData, Vector3D startPosition, Vector3D endPosition, CTraceFilter* pTraceFilter, int PenetrationCount)
{
	typedef void(__fastcall* oCreateTrace)(CTraceData*, Vector3D, Vector3D, CTraceFilter*, int, int);
	static oCreateTrace CreateTrace = (oCreateTrace)Utils::Memory::SignatureScan("client.dll", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC ? F2 0F 10 02");
	CreateTrace(pTraceData, startPosition, endPosition, pTraceFilter, PenetrationCount, 1); 
}

void TraceManager::InitGameTrace(CGameTrace* pTrace)
{
	typedef void(__fastcall* oInitTrace)(CGameTrace* pTrace);
	static oInitTrace InitTrace = (oInitTrace)Utils::Memory::SignatureScan("client.dll", "40 55 41 55 41 57 48 83 EC");
	InitTrace(pTrace);
}

void TraceManager::GetTraceInformation(CTraceData* pTraceData, CGameTrace* pGameTrace, float unkown, void* array)
{
	typedef void(__fastcall* oGetTraceInformation)(CTraceData*, CGameTrace*, float, void*);
	static oGetTraceInformation GetTraceInformation = (oGetTraceInformation)Utils::Memory::SignatureScan("client.dll", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 81 EC 80 00 00 00 48 8B E9 0F 29 74 24");
	GetTraceInformation(pTraceData, pGameTrace, unkown, array);
}


C_BaseEntity* TraceManager::TraceLine(Vector3D startPosition, Vector3D endPosition, C_CSPlayerPawn* target)
{
	CRay ray{};
	CGameTrace trace{};

	CTraceFilter filter{ Globals::LocalPlayerPawn, MASK_PLAYER_VISIBLE , 3 , 15 };

	if (TraceShape(startPosition, endPosition, &ray, &filter, &trace))
	{
		if (trace.Entity && trace.Hitbox && trace.Hitbox->BoneName != "invalid_bone")
		{
			return trace.Entity;
		}
	}
}

bool TraceManager::TraceShape(Vector3D startPosition, Vector3D endPosition, CRay* pRay, CTraceFilter* pTraceFilter, CGameTrace* pTrace)
{
	typedef bool(__fastcall* oTraceShape)(void*, CRay*, Vector3D, Vector3D, CTraceFilter*, CGameTrace*);
	static oTraceShape TraceShape = (oTraceShape)(Utils::Memory::SignatureScan("client.dll", "48 89 54 24 ? 48 89 4C 24 ? 55 53 56 57 41 56 41 57 48 8D AC 24 ? ? ? ? B8"));
	static void* CVPhys2World = *(void***)(Utils::Memory::RelativeAddress(Utils::Memory::SignatureScan("client.dll", "48 8B 0D ? ? ? ? 48 8D 94 24 ? ? ? ? 4C 8B CF"), 3, 7));

	if (!CVPhys2World)
		return false;

	return TraceShape(CVPhys2World, pRay, startPosition, endPosition, pTraceFilter, pTrace);
}

void PenetrationSystem::ScaleDamage(const int HitGroup, C_CSPlayerPawn* pPawn, const float WeaponArmorRatio, const float HeadshotMultiplier, float* DamageToScale)
{
	float headDamageScale = 1.f; 
	float bodyDamageScale = 1.f;

	switch (HitGroup)
	{
	case HITGROUP_HEAD:
		*DamageToScale *= headDamageScale * HeadshotMultiplier;
		break;
	case HITGROUP_CHEST:
	case HITGROUP_LEFTARM:

	case HITGROUP_RIGHTARM:
	case HITGROUP_NECK:
		*DamageToScale *= bodyDamageScale;
		break;
	case HITGROUP_STOMACH:
		*DamageToScale *= 1.25f * bodyDamageScale;
		break;
	case HITGROUP_LEFTLEG:
	case HITGROUP_RIGHTLEG:
		*DamageToScale *= 0.75f * bodyDamageScale;
		break;
	}

	if (!pPawn->GetItemServcices()->HasPlayerArmor(HitGroup))
		return;

	const int armor = pPawn->GetArmor();
	float HeavyArmorBonus = 1.0f, ArmorBonus = 0.5f, ArmorRatio = WeaponArmorRatio * 0.5f;

	float DamageToHealth = *DamageToScale * ArmorRatio;
	const float DamageToArmor = (*DamageToScale - DamageToHealth) * (HeavyArmorBonus * ArmorBonus);

	if (DamageToArmor > static_cast<float>(armor))
		DamageToHealth = *DamageToScale - static_cast<float>(armor) / ArmorBonus;

	*DamageToScale = DamageToHealth;
}

bool PenetrationSystem::SimulateFireBullet(Vector3D vecStartPos, Vector3D vecEndPos, C_CSPlayerPawn* pTarget, C_CSWeapon* pCurrentWeapon, PenetrationData& penetrationData)
{
	if (!pTarget)
		return false;

	using fn = void(__thiscall*)(void*);
	static auto InitTraceData = (fn)Utils::Memory::SignatureScan("client.dll", "48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8D 79 ? 33 F6 C7 47");

	if (pTarget == Globals::LocalPlayerPawn)
		return false;

	CCSWeaponBaseVData* pWeaponInfo = pCurrentWeapon->GetWeaponData();
	if (!pWeaponInfo)
		return false;

	Vector3D direction = (vecEndPos - vecStartPos).Normalize() * pWeaponInfo->GetRange();

	CTraceFilter traceFilter{ Globals::LocalPlayerPawn, 0x1C300B, 3, 15 }; 

	HandleBulletPenetrationData bulletHandleData = { (float)(pWeaponInfo->GetBaseDamage()), pWeaponInfo->GetPenetration(),pWeaponInfo->GetRange(), pWeaponInfo->GetRangeModifier(), 4, false };
	CTraceData traceData{ };
	InitTraceData(&traceData);

	TraceManager::CreateTrace(&traceData, vecStartPos, direction, &traceFilter, 4);

	float MaxRange = pWeaponInfo->GetRange();
	float TraceLenght{};
	float correctedDmg = (float)pWeaponInfo->GetBaseDamage();
	float rangeModifier = pWeaponInfo->GetRangeModifier();
	float armorRatio = pWeaponInfo->GetArmorRatio();
	float headshotMultiplier = pWeaponInfo->GetHeadshotMultiplier();

	for (int i = 0; i < traceData.NumUpdateValues; i++)
	{
		CUpdateValue* pUpdateValue = &traceData.UpdateValuesPointer[i];
		int index = pUpdateValue->HandleIndex & 0x7FFF;
		CGameTrace gameTrace{};
		TraceManager::InitGameTrace(&gameTrace);
		TraceManager::GetTraceInformation(&traceData, &gameTrace, 0.0f, &traceData.Element(index));

		if (gameTrace.Entity && gameTrace.Entity->IsEntityPlayer() && gameTrace.Entity == pTarget)
		{
			C_CSPlayerPawn* Player = static_cast<C_CSPlayerPawn*>(gameTrace.Entity);

			PenetrationSystem::ScaleDamage(gameTrace.Hitbox->GroupID, Player, armorRatio, headshotMultiplier, &correctedDmg);

			penetrationData.Damage = correctedDmg;
			penetrationData.Penetrated = (i > 0);
			penetrationData.PenetrationCount = i;

			return true;
		}

		if (PenetrationSystem::HandleBulletPenetration(&traceData, &bulletHandleData, pUpdateValue, Globals::LocalPlayerPawn->GetTeamNum()))
			break;

		correctedDmg = bulletHandleData.Damage;

	}

	return false;
}

float PenetrationSystem::GetDamage(Vector3D vecStartPos, Vector3D vecEndPos, C_CSPlayerPawn* pTarget, C_CSWeapon* pCurrentWeapon)
{
	float dmg = 0;

	PenetrationData data{};

	if (SimulateFireBullet(vecStartPos, vecEndPos, pTarget, pCurrentWeapon, data))
		dmg = data.Damage;

	return dmg;
}

bool PenetrationSystem::HandleBulletPenetration(CTraceData* traceData, HandleBulletPenetrationData* bulletData, CUpdateValue* modValues, int playerTeam)
{
	typedef bool(__fastcall* fn)(CTraceData* traceData, HandleBulletPenetrationData* bulletData, CUpdateValue* modValues, int playerTeam, void* unknown);
	static fn oHandleBulletPenetration = (fn)Utils::Memory::SignatureScan("client.dll", "48 8B C4 44 89 48 ?? 48 89 50 ?? 48 89 48 ?? 55 57");

	bool valid = oHandleBulletPenetration(traceData, bulletData, modValues, playerTeam, nullptr);

	return valid;
}
