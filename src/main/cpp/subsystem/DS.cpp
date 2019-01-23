#include <subsystem/DS.hpp>

DS::DS()
{
	cam0.SetFPS(20);
	cam0.SetResolution(160, 120);
	cam0.SetExposureManual(-30);
	cam0.SetWhiteBalanceManual(4500);
	cam0.SetBrightness(-100);

	chooseController.SetDefaultOption(sPS4, sPS4);
	chooseController.AddOption(sXBX, sXBX);
	frc::SmartDashboard::PutData("Selected Controller", &chooseController);
}
bool DS::CVStuff()
{
	cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
	cv::Mat frame0;
	cvSink.GrabFrame(frame0);
	std::string path = "/u/vision" + std::to_string(imNum) + ".jpg" ;
	imwrite(path, frame0);
	imNum++;
	return true;
}