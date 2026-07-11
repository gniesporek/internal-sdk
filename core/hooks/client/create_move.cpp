#include "../hooks.h"

void CreateMove::hkCreateMove(CCSGOInput* a1, int a2, char a3)
{
	Prediction::RunClientPrediction(PredictionStage::CLIENT_COMMAND_TICK);

	oCreateMove(a1, a2, a3);

}
