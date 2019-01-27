#include "subsystem/Vision.hpp"

Vision::Vision()
{
	// camera.SetFPS(20);
	// camera.SetResolution(160, 120);
	// camera.SetExposureManual(15); //20 worked well
	// camera.SetWhiteBalanceManual(4500);
	// camera.SetBrightness(-300);
}
double Vision::Run(){
    // cs::CvSink cvSink = CameraServer::GetInstance()->GetVideo();
	// cv::Mat frame0;
	// cvSink.GrabFrame(frame0);
	// std::string path = "/u/vision" + std::to_string(imNum) + ".jpg" ;
	// imwrite(path, frame0);
	// imNum++;

	if(CVT){
	camera.SetExposureManual(15); //20 worked well
	camera.SetBrightness(-300);
	camera.SetWhiteBalanceManual(4500);
	}
	else{
	camera.SetExposureAuto();
	camera.SetWhiteBalanceAuto();
	camera.SetBrightness(40);
	}

	cv::Mat source;
    cvSink.GrabFrame(source);
	if(CVT && !source.empty()){
		VP.Process(source);
    	outputStreamStd.PutFrame(*VP.GetHslThresholdOutput());
		imwrite(path, *VP.GetHslThresholdOutput());
		imNum++;

		double realCenter = 0;
		auto centers = contourCenters(*VP.GetFilterContoursOutput());
		for(auto c : centers){
			if(centers.size() < 2){
				realCenter += c.x; 
			}
		}
		realCenter /= centers.size();
		if((realCenter != 80) && (realCenter > 0)){
    	double error = (realCenter - 80) / 160;
		return error;
		}
	}

	// if(!frame0.empty()){
	// 	//VP.Process(frame0);
	// 	cs::CvSource outputStreamStd = CameraServer::GetInstance()->PutVideo("HSLThresh", 160, 120);
	// 	outputStreamStd.PutFrame(frame0/**VP.GetHslThresholdOutput()*/);
	// }
	return -1;
}
void Vision::Init(){
	camera = CameraServer::GetInstance()->StartAutomaticCapture();
    cvSink = CameraServer::GetInstance()->GetVideo();
    outputStreamStd = CameraServer::GetInstance()->PutVideo("Gray", 160, 120);
	camera.SetFPS(20);
	camera.SetResolution(160, 120);
}
void Vision::CVMode(bool On){
	CVT = On;
}

cv::Point Vision::centerOfContour(std::vector<cv::Point> contour) {
	double totalx=0.0; //given a contour, outputs its center
	double totaly=0.0;
	for(int d=0; d<contour.size();d++) {
		totalx+=contour[d].x;
		totaly+=contour[d].y;
	}
	cv::Point pt;
	pt.x=totalx/contour.size();
	pt.y=totaly/contour.size();
	return pt;
}

std::vector<cv::Point> Vision::contourCenters(std::vector<std::vector<cv::Point>> contours) {
	std::vector<cv::Point> centers; //given a vector of contours, outputs a vector consisting of their centers
	double totalx;
	double totaly;
	for(int c=0;c<contours.size();c++) {
		centers.push_back(centerOfContour(contours[c]));
	}
	return centers;
}