#include <subsystem/DS.hpp>

DS::DS()
{

	chooseController.SetDefaultOption(sPS4, sPS4);
	chooseController.AddOption(sXBX, sXBX);

	chooseDriveLimit.AddOption(sLimit, sLimit);
	chooseDriveLimit.SetDefaultOption(sUnlimitted, sUnlimitted);

	chooseElevatorLimit.SetDefaultOption(sLimit, sLimit);
	chooseElevatorLimit.AddOption(sUnlimitted, sUnlimitted);

	chooseWristLimit.AddOption(sLimit, sLimit);
	chooseWristLimit.SetDefaultOption(sUnlimitted, sUnlimitted);

}
void DS::SmartDash() {
	frc::SmartDashboard::PutData("Selected Controller", &chooseController);
	frc::SmartDashboard::PutData("Drive Limits", &chooseDriveLimit);
	frc::SmartDashboard::PutData("Elevator Limits", &chooseElevatorLimit);
	frc::SmartDashboard::PutData("Wrist Limits", &chooseWristLimit);
}