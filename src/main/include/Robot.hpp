/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/livewindow/LiveWindow.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include "auto/AutoPrograms.hpp"
#include <string>
#include "robotmap.hpp"
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <opencv2/videoio.hpp>
#include <frc/PowerDistributionPanel.h>
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
  void DisabledInit() override;

private:
  robotmap IO;
  AutoPrograms autoPrograms{IO};
  LiveWindow &m_lw = *frc::LiveWindow::GetInstance();

  const double deadband = 0.1;

  bool hatchPresets = false;
  bool stopAuton;
  double elevCmd = 0;
  Timer hatchDeploy;
  bool initOneShot = false;
  bool drivePresetOneshot = false;
  bool cargoWristPreset = false;
  bool controlModeOneShot = true;

  // Dont update smart dash every loop
  int smartDashSkip = 0;

  Timer autoLog;

  double Deadband(double input, double deadband);
  void UpdateSD();

  bool AutoTarget(bool Go, double forward);

  PowerDistributionPanel *pdp = new PowerDistributionPanel();
};
