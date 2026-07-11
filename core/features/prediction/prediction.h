#pragma once

enum class PredictionStage : int {
	CLIENT_COMMAND_TICK = 0,
	DEMO_PREENTITY,
	DEMO_SIMULATION,
	POSTNETUPDATE,
	SERVER_STARVED_AND_ADDED_USERCMD,
	CLIENT_FRAME_SIMULATE,
};

class Prediction {
public:
	static void RunClientPrediction(PredictionStage predictionStage);
private:

};