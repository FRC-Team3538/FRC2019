#pragma once

#include <RJVisionPipeline.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <cameraserver/CameraServer.h>
#include <iostream>
#include <math.h>
#include <frc/smartDashboard/SmartDashboard.h>
#include <frc/Timer.h>

using namespace frc;
using namespace cv;
using namespace grip;
using namespace std;

class Vision
{
  private:
    RJVisionPipeline VP;
    double centerX = 0.0;
    int imNum = 1;

  public:
    cs::UsbCamera cam0 = CameraServer::GetInstance()->StartAutomaticCapture("Camera 0", 0);
    cs::VideoSink server = CameraServer::GetInstance()->GetServer();
    cs::CvSink sink0;
    cs::UsbCamera camera;
    cs::CvSink cvSink;
    cs::CvSource outputStreamStd;
    std::string path = "/u/vision" + std::to_string(imNum) + ".jpg" ;
    bool CVT = false;


    Timer time;
    int contourNum = 0;
    void Run();
    void Init();
    void CVMode(bool On);
    cv::Point centerOfContour(std::vector<cv::Point> contour);
    std::vector<cv::Point> contourCenters(std::vector<std::vector<cv::Point>> contours);
    std::vector<std::vector<cv::Point>> lines;
    std::vector<cv::Point> singleContour(std::vector<std::vector<cv::Point>> contours, int numero);
    void DrawLine(Vec4f elLine, cv::Mat img);
    double vectorAngle(Vec4f vector);
    //double contourAngle(std::vector<cv::Point> contour); //Degrees

    double prevError = 0;

    struct contourData{
      double x, angle;
      int numero;
    };

    struct returnData{
      double cmd, distance;
      bool data = false;
    };
    returnData data;

    std::vector<contourData> contourDataVector;

    Vision();
};