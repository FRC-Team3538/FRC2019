#include <subsystem/DS.hpp>

DS::DS()
{

	chooseController.SetDefaultOption(sPS4, sPS4);
	chooseController.AddOption(sXBX, sXBX);

	chooseDriveLimit.SetDefaultOption(sLimit, sLimit);
	chooseDriveLimit.AddOption(sUnlimitted, sUnlimitted);

	chooseElevatorLimit.SetDefaultOption(sLimit, sLimit);
	chooseElevatorLimit.AddOption(sUnlimitted, sUnlimitted);

	chooseWristLimit.SetDefaultOption(sLimit, sLimit);
	chooseWristLimit.AddOption(sUnlimitted, sUnlimitted);

}
void DS::SmartDash() {
	frc::SmartDashboard::PutData("Selected Controller", &chooseController);
	frc::SmartDashboard::PutData("Drive Limits", &chooseDriveLimit);
	frc::SmartDashboard::PutData("Elevator Limits", &chooseElevatorLimit);
	frc::SmartDashboard::PutData("Wrist Limits", &chooseWristLimit);
}