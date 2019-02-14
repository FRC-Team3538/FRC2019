#include <subsystem/DS.hpp>

DS::DS()
{

	chooseController.SetDefaultOption(sPS4, sPS4);
	chooseController.AddOption(sXBX, sXBX);
	frc::SmartDashboard::PutData("Selected Controller", &chooseController);
}
void DS::SmartDash() {
	frc::SmartDashboard::PutData("Selected Controller", &chooseController);
}