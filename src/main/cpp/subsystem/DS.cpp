#include <subsystem/DS.h>

DS::DS(){
	cam0.SetFPS(30);
	cam0.SetResolution(160, 120);
	cam0.SetExposureAuto();
	cam0.SetWhiteBalanceAuto();

	AM.chooseAutoProgram.AddObject(AM.AutoLine, AM.AutoLine);
	AM.chooseAutoProgram.AddDefault(AM.AutoNone, AM.AutoNone);
	frc::SmartDashboard::PutData("Auto Mode", &AM.chooseAutoProgram);
}
