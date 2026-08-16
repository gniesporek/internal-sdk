#include "c_user_cmd.h"

//  initialize usercmd
CUserCmd* CUserCmd::GetUserCmd(CCSPlayerController* pController)
{
	int32_t tick = 0;
	GetPlayerTick(pController, &tick);
	if (tick == -1)
		return nullptr;

	CUserCmdArray* userCmdArray = CUserCmdArray::Get(CUserCmdArray::GetArrayCommands(), tick - 1);

	return userCmdArray ? Get(pController, userCmdArray->m_nCommandNumber) : nullptr;
}
//  __int64 __fastcall sub_8BCC90(__int64 a1, int a2) the one that returns the usercmd instead of __int64 __fastcall sub_8C8C20(__int64 a1, int a2) in the CreateMove v154 = sub_8C8C20((__int64)v17, v10); both looking the same
CUserCmd* CUserCmd::Get(CCSPlayerController* pController, uint32_t nCmd)
{
	typedef CUserCmd* (__fastcall* GetUserCmdFn)(CCSPlayerController*, uint32_t);
	static auto GetUserCmd = (GetUserCmdFn)(Utils::Memory::SignatureScan("client.dll", "40 53 48 83 EC ? 8B DA E8 ? ? ? ? 4C 8B C0"));
	if (!GetUserCmd)
		return nullptr;

	return GetUserCmd(pController, nCmd);
}

//  int *__fastcall sub_14BF730(__int64 a1, int *a2)
void CUserCmd::GetPlayerTick(CCSPlayerController* pController, int32_t* nCmd)
{
	typedef void(__fastcall* GetPlayerTickFn)(CCSPlayerController*, int32_t*);
	static auto GetPlayerTick = (GetPlayerTickFn)(Utils::Memory::SignatureScan("client.dll", "48 83 EC ? 4C 8B 0D ? ? ? ? 4C 8B DA"));
	if (!GetPlayerTick)
		return;
	GetPlayerTick(pController, nCmd);
}

//  wrapper  __int64 __fastcall sub_8BCE90(__int64 a1, int a2)
CUserCmdArray* CUserCmdArray::Get(CUserCmd** pUserCmd, int nTick)
{
	typedef CUserCmdArray* (__fastcall* GetArrayCommandsFn)(CUserCmd**, int);
	static auto GetArrayCommands = (GetArrayCommandsFn)(Utils::Memory::SignatureScan("client.dll", "48 89 4C 24 ? 41 56 41 57"));
	if (!GetArrayCommands)
		return nullptr;

	return GetArrayCommands(pUserCmd, nTick);
}

// wrapper  v9 = sub_8BCE90((__int64)off_2028C10, v8); off_2028C10  3,7 relative ptr 
CUserCmd** CUserCmdArray::GetArrayCommands()
{
	static auto GetArrayUserCmd = *(CUserCmd***)((Utils::Memory::RelativeAddress(Utils::Memory::SignatureScan("client.dll", "48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B CF 4C 8B F8"), 3, 7)));
	if (!GetArrayUserCmd)
		return nullptr;

	return GetArrayUserCmd;
}

void CUserCmd::SetInputHistoryAngle(Vector3D* vecAngle)
{
	RepeatedPtrField_t<CSGOInputHistoryEntryPB>& inputHistory = this->CSGOUserCmd.InputHistoryEntry;

	for (int i = 0; i < inputHistory.nCurrentSize; i++)
	{
		CSGOInputHistoryEntryPB* entry = nullptr;

		if (i < inputHistory.pRep->nAllocatedSize)
			entry = inputHistory.pRep->tElements[i];

		if (!entry || !entry->ViewAngles)
			continue;

		entry->SetBits(INPUT_HISTORY_BITS_VIEWANGLES);
		entry->ViewAngles->Angle = *vecAngle;
	}

}

void CUserCmd::SetInputHistory(int renderTick, C_CSPlayerPawn* pLocal, CCSPlayerController* pController)
{
	RepeatedPtrField_t<CSGOInputHistoryEntryPB>& inputHistory = this->CSGOUserCmd.InputHistoryEntry;
	int size = inputHistory.nCurrentSize;
	int totalSize = inputHistory.nTotalSize;

	float interpTime = pLocal->GetInterpolationTiming(0, 1);
	TimeStamp interpolationTime(interpTime);

	for (int i = 0; i < size; i++)
	{
		CSGOInputHistoryEntryPB* entry = nullptr;

		if (i < inputHistory.pRep->nAllocatedSize)
			entry = inputHistory.pRep->tElements[i];

		if (!entry || !entry->ViewAngles)
			continue;
		entry->SetBits(INPUT_HISTORY_BITS_PLAYER_TICK_COUNT);
		entry->PlayerTickCount = pController->GetTickBase();
		entry->SetBits(INPUT_HISTORY_BITS_PLAYER_TICK_FRACTION);
		entry->PlayerTickFraction = 0.f;

		entry->SetBits(INPUT_HISTORY_BITS_RENDER_TICK_COUNT);
		entry->RenderTickCount = renderTick + interpolationTime.tick;
		entry->SetBits(INPUT_HISTORY_BITS_RENDER_TICK_FRACTION);
		entry->RenderTickFraction = 0.f;
	}
}

CSubtickMoveStep* CBaseUserCmdPB::CreateSubTickMoveStep()
{

	if (this->SubtickMoves.pRep && this->SubtickMoves.nCurrentSize < this->SubtickMoves.pRep->nAllocatedSize)
		return this->SubtickMoves.pRep->tElements[this->SubtickMoves.nCurrentSize++];
	CSubtickMoveStep* subtickMoveStep = CSubtickMoveStep::Create(nullptr);
	this->SubtickMoves.Add(subtickMoveStep);
	return subtickMoveStep;
}

CSubtickMoveStep* CSubtickMoveStep::Create(void* pRep)
{
	typedef CSubtickMoveStep* (__fastcall* CreateSubtickMoveStepFn)(void* pRep);
	static auto CreateSubtickMoveStep = (CreateSubtickMoveStepFn)(Utils::Memory::RelativeAddress(Utils::Memory::SignatureScan("client.dll", "E8 ? ? ? ? 48 8B D0 48 8B CF E8 ? ? ? ? 48 8B D0"), 1, 5));
	return CreateSubtickMoveStep(pRep);
}

void CSubtickMoveStep::AddButton(uint64_t button, float when, bool pressed)
{
	this->SetBits(ESubtickMoveStepBits::MOVESTEP_BITS_BUTTON);
	this->Buttons = button;
	this->SetBits(ESubtickMoveStepBits::MOVESTEP_BITS_WHEN);
	this->When = when;
	this->SetBits(ESubtickMoveStepBits::MOVESTEP_BITS_PRESSED);
	this->Pressed = pressed;
}