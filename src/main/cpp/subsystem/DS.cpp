#include <subsystem/DS.h>

DS::DS(){
	cam0.SetFPS(30);
	cam0.SetResolution(160, 120);
	cam0.SetExposureAuto();
	cam0.SetWhiteBalanceAuto();


    chooseController.AddDefault(sPS4, sPS4);
	chooseController.AddObject(sXBX, sXBX);
	frc::SmartDashboard::PutData("Selected Controller", &chooseController);
}
