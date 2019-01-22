#include <subsystem/DS.hpp>

DS::DS()
{
	cam0.SetFPS(20);
	cam0.SetResolution(160, 120);
	cam0.SetExposureManual(-50);
	cam0.SetWhiteBalanceManual(4500);
	cam0.SetBrightness(-100);

	chooseController.AddDefault(sPS4, sPS4);
	chooseController.AddOption(sXBX, sXBX);
	frc::SmartDashboard::PutData("Selected Controller", &chooseController);
}
bool DS::CVStuff()
{
	int imNum = 1;
	cv::VideoCapture camera0(0);
	cv::Mat3b frame0;
	camera0 >> frame0;
	Mat save_img; camera0 >> save_img;
	imwrite("test.jpg", save_img);
	imNum++;
	return true;
}