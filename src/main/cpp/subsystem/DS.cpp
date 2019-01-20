#include <subsystem/DS.hpp>

DS::DS(){
	cam0.SetFPS(30);
	cam0.SetResolution(160, 120);
	cam0.SetExposureAuto();
	cam0.SetWhiteBalanceAuto();


    chooseController.SetDefaultOption(sPS4, sPS4);
	chooseController.AddOption(sXBX, sXBX);
	frc::SmartDashboard::PutData("Selected Controller", &chooseController);
}