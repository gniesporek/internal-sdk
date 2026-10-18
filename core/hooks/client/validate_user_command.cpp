#include "../hooks.h"

void __fastcall ValidateUserCommand::hkValidateUserCommand(CCSGOInput* input, int slot)
{
	Vector3D originalViewAngles = *input->GetViewAngles();

	Globals::CameraViewAngles = originalViewAngles;

	oValidateUserCommand(input, slot);
	input->SetViewAngles(originalViewAngles);
}
