#pragma once
#include "../../valve/vectors/vectors.h"
#include "../structs/colors.h"

#include <unordered_map>

// ported from History for poseidon Engine Valve Convars on2e4bf32 Commits on Mar 9, 2026 //

// dissasembled https://imgur.com/a/E3CUNKR

#define FCVAR_NONE 0
#define FCVAR_LINKED_CONCOMMAND (1 << 0)
#define FCVAR_DEVELOPMENTONLY (1 << 1)
#define FCVAR_GAMEDLL (1 << 2)
#define FCVAR_CLIENTDLL (1 << 3)
#define FCVAR_HIDDEN (1 << 4)
#define FCVAR_PROTECTED (1 << 5)
#define FCVAR_SPONLY (1 << 6)
#define FCVAR_ARCHIVE (1 << 7)
#define FCVAR_NOTIFY (1 << 8)
#define FCVAR_USERINFO (1 << 9)
#define FCVAR_SOMETHING_THAT_HIDES (1 << 10) // Actual name unavailable
#define FCVAR_UNLOGGED (1 << 11)
#define FCVAR_MISSING1 (1 << 12)
#define FCVAR_REPLICATED (1 << 13)
#define FCVAR_CHEAT (1 << 14)
#define FCVAR_PER_USER (1 << 15)
#define FCVAR_DEMO (1 << 16)
#define FCVAR_DONTRECORD (1 << 17)
#define FCVAR_MISSING2 (1 << 18)
#define FCVAR_RELEASE (1 << 19)
#define FCVAR_MENUBAR_ITEM (1 << 20)
#define FCVAR_MISSING3 (1 << 21)
#define FCVAR_NOT_CONNECTED (1 << 22)
#define FCVAR_VCONSOLE_FUZZY_MATCHING (1 << 23)
#define FCVAR_SERVER_CAN_EXECUTE (1 << 24)
#define FCVAR_MISSING4 (1 << 25)
#define FCVAR_SERVER_CANNOT_QUERY (1 << 26)
#define FCVAR_VCONSOLE_SET_FOCUS (1 << 27)
#define FCVAR_CLIENTCMD_CAN_EXECUTE (1 << 28)
#define FCVAR_EXECUTE_PER_TICK (1 << 29)

union CVarValue
{
	bool i1;
	short i16;
	uint16_t u16;
	int i32;
	uint32_t u32;
	int64_t i64;
	uint64_t u64;
	float fl;
	double db;
	const char* sz;
	Colors clr;
	Vector2D vec2;
	Vector3D vec3;
	Vector4D vec4;
	Vector4D ang;
};

class CConVar
{
public:
	const char* szName;
	CVarValue* m_pDefaultValue;
	PAD(0x10);
	const char* szDescription;
	uint32_t nType;
	uint32_t nRegistered;
	uint32_t nFlags;
	PAD(0x24);
	CVarValue value;
};

// cvarlist tier0.dll decompile
class IEngineCvar {
public:
	CConVar* FindVar(const char* convarName);
	CConVar* GetConVar(const char* name);
	void Setup();
	static inline std::unordered_map<uint32_t, uintptr_t> ConvarMap;
private:
	CConVar* GetConvarByIndex(uint64_t index);
	void GetFirstConvarIndex(uint64_t& index);
	void GetNextConvarIndex(uint64_t& index);
};