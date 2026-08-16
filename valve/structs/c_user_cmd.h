#pragma once
#include "../../core/utils/utils.h"

#include "../../valve/vectors/vectors.h"

#include "../classes/classes.h"

enum ECommandButtons : std::uint64_t
{
	IN_ATTACK = 1 << 0,
	IN_JUMP = 1 << 1,
	IN_DUCK = 1 << 2,
	IN_FORWARD = 1 << 3,
	IN_BACK = 1 << 4,
	IN_USE = 1 << 5,
	IN_LEFT = 1 << 7,
	IN_RIGHT = 1 << 8,
	IN_MOVELEFT = 1 << 9,
	IN_MOVERIGHT = 1 << 10,
	IN_SECOND_ATTACK = 1 << 11,
	IN_RELOAD = 1 << 13,
	IN_SPRINT = 1 << 16,
	IN_JOYAUTOSPRINT = 1 << 17,
	IN_SHOWSCORES = 1ULL << 33,
	IN_ZOOM = 1ULL << 34,
	IN_LOOKATWEAPON = 1ULL << 35
};

enum EInputHistoryBits : std::uint32_t
{
	INPUT_HISTORY_BITS_VIEWANGLES = 0x00000001u,
	INPUT_HISTORY_BITS_RENDER_TICK_COUNT = 0x00000200u,
	INPUT_HISTORY_BITS_RENDER_TICK_FRACTION = 0x00000400u,
	INPUT_HISTORY_BITS_PLAYER_TICK_COUNT = 0x00000800u,
	INPUT_HISTORY_BITS_PLAYER_TICK_FRACTION = 0x00001000u,
	INPUT_HISTORY_BITS_CL_INTERP = 0x00000002u,
	INPUT_HISTORY_BITS_SV_INTERP0 = 0x00000004u,
	INPUT_HISTORY_BITS_SV_INTERP1 = 0x00000008u,
	INPUT_HISTORY_BITS_PLAYER_INTERP = 0x00000010u,
	INPUT_HISTORY_BITS_FRAME_NUMBER = 0x00002000u,
	INPUT_HISTORY_BITS_TARGET_ENT_INDEX = 0x00004000u,
	INPUT_HISTORY_BITS_SHOOT_POSITION = 0x00000020u,
	INPUT_HISTORY_BITS_TARGET_HEAD_POS_CHECK = 0x00000040u,
	INPUT_HISTORY_BITS_TARGET_ABS_POS_CHECK = 0x00000080u,
	INPUT_HISTORY_BITS_TARGET_ABS_ANG_CHECK = 0x00000100u
};

enum EButtonStatePBBits : uint32_t
{
	BUTTON_STATE_PB_BITS_BUTTONSTATE1 = 0x1U,
	BUTTON_STATE_PB_BITS_BUTTONSTATE2 = 0x2U,
	BUTTON_STATE_PB_BITS_BUTTONSTATE3 = 0x4U
};

enum EBaseCmdBits : std::uint32_t
{
	BASE_BITS_LEGACY_COMMAND_NUMBER = 0x00000010u,
	BASE_BITS_CLIENT_TICK = 0x00000020u,
	BASE_BITS_PREDICTION_OFFSET_X256 = 0x00004000u,
	BASE_BITS_BUTTONS = 0x00000002u,
	BASE_BITS_VIEWANGLES = 0x00000004u,
	BASE_BITS_FORWARDMOVE = 0x00000040u,
	BASE_BITS_LEFTMOVE = 0x00000080u,
	BASE_BITS_UPMOVE = 0x00000100u,
	BASE_BITS_IMPULSE = 0x00000200u,
	BASE_BITS_WEAPONSELECT = 0x00000400u,
	BASE_BITS_RANDOMSEED = 0x00000800u,
	BASE_BITS_MOUSEDX = 0x00001000u,
	BASE_BITS_MOUSEDY = 0x00002000u,
	BASE_BITS_PAWN_ENTITY_HANDLE = 0x00020000u,
	BASE_BITS_MOVE_CRC = 0x00000001u,
	BASE_BITS_CONSUMED_SERVER_ANGLES = 0x00008000u,
	BASE_BITS_CMD_FLAGS = 0x00010000u,
	BASE_BITS_EXECUTION_NOTES = 0x00000008u
};

enum ECSGOUserCmdBits : std::uint32_t
{
	CSGOUSERCMD_BITS_BASE = 0x00000001u,
	CSGOUSERCMD_BITS_ATTACK1_START_HISTORY_INDEX = 0x00000020u,
	CSGOUSERCMD_BITS_ATTACK2_START_HISTORY_INDEX = 0x00000040u,
	CSGOUSERCMD_BITS_LEFT_HAND_DESIRED = 0x00000002u,
	CSGOUSERCMD_BITS_IS_PREDICTING_BODY_SHOT_FX = 0x00000004u,
	CSGOUSERCMD_BITS_IS_PREDICTING_HEAD_SHOT_FX = 0x00000008u,
	CSGOUSERCMD_BITS_IS_PREDICTING_KILL_RAGDOLLS = 0x00000010u
};

enum ESubtickMoveStepBits : uint32_t {
	MOVESTEP_BITS_BUTTON = 0x00000001u,
	MOVESTEP_BITS_PRESSED = 0x00000002u,
	MOVESTEP_BITS_WHEN = 0x00000004u,
	MOVESTEP_BITS_ANALOG_FORWARD_DELTA = 0x00000008u,
	MOVESTEP_BITS_ANALOG_LEFT_DELTA = 0x00000010u,
	MOVESTEP_BITS_ANALOG_PITCH_DELTA = 0x00000020u,
	MOVESTEP_BITS_ANALOG_YAW_DELTA = 0x00000040u
};

class CBasePB {
public:
	PAD(0x8)
	std::uint32_t HasBits;
	std::uint64_t CachedBits;

	void SetBits(std::uint64_t nBits)
	{
		CachedBits |= nBits;
	}
};
static_assert(sizeof(CBasePB) == 0x18);

class CMsgQAngle {
public:
	PAD(0x18);
	Vector3D Angle;
};
static_assert(sizeof(CMsgQAngle) == 0x24);

class CCSGOInterpolationInfoPB_CL : public CBasePB
{
public:
	float Fraction; // 0x18
};

class CCSGOInterpolationInfoPB : public CBasePB
{
public:
	float Fraction; // 0x18
	int SrcTick; // 0x1C
	int DstTick; // 0x20

	void Zero()
	{
		this->Fraction = 0.f;
		this->SrcTick = this->DstTick = 0;
	}
};

class CSGOInputHistoryEntryPB : public CBasePB {
public:
	CMsgQAngle* ViewAngles;
	CCSGOInterpolationInfoPB_CL* ClInterp;
	CCSGOInterpolationInfoPB* SvInterp0;
	CCSGOInterpolationInfoPB* SvInterp1;
	CCSGOInterpolationInfoPB* PlayerInterp;
	CMsgQAngle* ShootPosition;
	CMsgQAngle* TargetHeadPositionCheck;
	CMsgQAngle* TargetAbsPositionCheck;
	CMsgQAngle* TargetAngPositionCheck;
	int32_t RenderTickCount;
	float RenderTickFraction;
	int32_t PlayerTickCount;
	float PlayerTickFraction;
	int32_t FrameNumber;
	int32_t TargetEntIndex;
};
static_assert(sizeof(CSGOInputHistoryEntryPB) == 0x78);

class CSubtickMoveStep : public CBasePB {
public:
	uint64_t Buttons;
	bool Pressed;
	float When;
	float AnalogForwardDelta;
	float AnalogLeftDelta;
	float AnalogPitchDelta;
	float AnalogYawDelta;


	static CSubtickMoveStep* Create(void* pRep);

	void AddButton(uint64_t button, float when, bool pressed);
};
static_assert(sizeof(CSubtickMoveStep) == 0x38);

class CInButtonStatePb : public CBasePB {
public:
	std::uint64_t ButtonPressed;
	std::uint64_t ButtonChanged;
	std::uint64_t ButtonScroll;
};

class CBaseUserCmdPB : public CBasePB {
public:
	RepeatedPtrField_t<CSubtickMoveStep> SubtickMoves; // 0x18
	PAD(0x8);
	CInButtonStatePb* ButtonState; // 0x38
	CMsgQAngle* ViewAngles; // 0x40
	void* ExecutionNotes; // 0x48
	int LegacyCommandNumber; // 0x50
	int ClientTick; // 0x54
	float ForwardMove; // 0x58
	float SideMove; // 0x5C
	float UpMove; // 0x60
	int Impulse; // 0x64
	int WeaponSelect; // 0x68
	int RandomSeed; // 0x6C
	int MouseDX; // 0x70
	int MouseDY; // 0x74
	uint32_t PredictionOffsetTicks256; // 0x78
	uint32_t ConsumedServerAnglesChanges; // 0x7C
	int CmdFlags; // 0x80
	uint16_t PawnEntityHandle; // 0x84

	CSubtickMoveStep* CreateSubTickMoveStep();

};
static_assert(sizeof(CBaseUserCmdPB) == 0x88);

class CInButtonState {
public:
	PAD(0x8);
	std::uint64_t Value;
	std::uint64_t ValueChanged;
	std::uint64_t ValueScroll;
};
static_assert(sizeof(CInButtonState) == 0x20);

class CCSGOUserCmd : public CBasePB {
public:
	RepeatedPtrField_t<CSGOInputHistoryEntryPB>  InputHistoryEntry;
	CBaseUserCmdPB* BaseUserCmd;
	bool LeftHandDesired;
	bool IsPredictingBodyShot;
	bool IsPredictingHeadShot;
	bool IsPredictingKillShot;
	int32_t Attack1StartHistoryIndex;
	int32_t Attack2StartHistoryIndex;
};
static_assert(sizeof(CCSGOUserCmd) == 0x48);

class CUserCmd {
public:
	static CUserCmd* GetUserCmd(CCSPlayerController* pController);

	PAD(0x8);
	uint32_t CommandNumber;
	CCSGOUserCmd CSGOUserCmd;
	CInButtonState ButtonState;

	void SetInputHistoryAngle(Vector3D* vecAngle);
	void SetInputHistory(int renderTick, C_CSPlayerPawn* pLocal, CCSPlayerController* pController);

private:
	static CUserCmd* Get(CCSPlayerController* pController, uint32_t nCmd);
	static void GetPlayerTick(CCSPlayerController* pController, int32_t* nCmd);
};
static_assert(sizeof(CUserCmd) == 0x78);

class CUserCmdArray {
public:
	PAD(0x5910);
	uint32_t m_nCommandNumber;
	static CUserCmdArray* Get(CUserCmd** pUserCmd, int nTick);
	static CUserCmd** GetArrayCommands();
};
static_assert(sizeof(CUserCmdArray) == 0x5914);