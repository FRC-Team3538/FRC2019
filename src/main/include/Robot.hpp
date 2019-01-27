/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/liveWindow/LiveWindow.h>
#include <frc/smartDashboard/SmartDashboard.h>
#include "auto/AutoPrograms.hpp"
#include <string>
#include "robotmap.hpp"
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <opencv2/videoio.hpp>
#include <subsystem/Vision.hpp>
using namespace cv;

class Robot : public frc::TimedRobot
{
public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

private:
  robotmap IO;
  Vision vision;
  AutoPrograms autoPrograms{IO};
  LiveWindow &m_lw = *frc::LiveWindow::GetInstance();

  const double deadband = 0.05;

  enum driveModes
  {
    ARCADE,
    TANKYTANK,
    HOLONOMIC
  };
  int driveMode = driveModes::ARCADE;

  double Deadband(double input, double deadband);
  void UpdateSD();

  bool AutoTarget();  
};
