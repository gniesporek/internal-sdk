#include "../hooks.h"

#include "../../../valve/structs/c_user_cmd.h"

void CreateMove::hkCreateMove(CCSGOInput* a1, int a2, char a3)
{
	Prediction::RunClientPrediction(PredictionStage::CLIENT_COMMAND_TICK);

	oCreateMove(a1, a2, a3);

	Globals::LocalPlayerPawn = C_CSPlayerPawn::GetLocalPlayer();
	if (!Globals::LocalPlayerPawn)
		return;

	Globals::LocalPlayerController = CCSPlayerController::GetLocalPlayer();
	if (!Globals::LocalPlayerController)
		return;

	CUserCmd* pUserCmd = CUserCmd::GetUserCmd(Globals::LocalPlayerController);
	if (!pUserCmd || !pUserCmd->CSGOUserCmd.BaseUserCmd || !pUserCmd->CSGOUserCmd.BaseUserCmd->ViewAngles)
		return;

	Assistance::Run(pUserCmd);

}
