#include "../features.h"

void Prediction::RunClientPrediction(PredictionStage predictionStage)
{
	typedef void(__fastcall* fnClientSidePrediction)(void*, PredictionStage);
	static auto ClientSidePrediction = (fnClientSidePrediction)(Utils::Memory::SignatureScan("engine2.dll", "40 55 41 56 48 83 EC ? 80 B9"));
	if (!ClientSidePrediction)
		return;

	if (!NetworkGameClientWrapper::pNetworkGameClientWrapper)
		return;

	ClientSidePrediction(NetworkGameClientWrapper::pNetworkGameClientWrapper, predictionStage);
}