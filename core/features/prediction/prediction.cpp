#include "../features.h"

void Prediction::RunClientPrediction(PredictionStage predictionStage)
{
	typedef void(__fastcall* fnClientSidePrediction)(void*, PredictionStage);
	static auto ClientSidePrediction = (fnClientSidePrediction)(Utils::Memory::SignatureScan("engine2.dll", "40 55 41 56 48 83 EC ? 80 B9"));
	if (!ClientSidePrediction)
		return;

	static uintptr_t NetworkGameClient = *(uintptr_t*)(Utils::Memory::RelativeAddress(Utils::Memory::SignatureScan("engine2.dll", "48 89 1D ? ? ? ? 48 8D 15 ? ? ? ? 48 8B 07"), 3, 7));

	if (!NetworkGameClient)
		return;

	ClientSidePrediction((void*)NetworkGameClient, predictionStage);
}