/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <frc/IterativeRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include "Logging.h"
#include "PS4Controller.h"
#include <ctre/Phoenix.h>
#include <frc/Timer.h>
#include <frc/PowerDistributionPanel.h>
#include <frc/smartdashboard/SmartDashboard.h>

using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::motorcontrol;
using namespace frc;
using namespace std;

class Robot : public frc::IterativeRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledPeriodic() override;
  void TestPeriodic() override;

 private:

  WPI_TalonSRX Elev{6};

  void VelControl(double run);
  void Set(double speed);
  void SetPosition(double pos);
  double Deadband(double input, double deadband);

  PS4Controller DriverPS{0};
  PS4Controller OperatorPS{1};

  Logging logging;
  Timer autoLog;
  PowerDistributionPanel *pdp = new PowerDistributionPanel();

  const double kScaleFactor = (75.0 - 9.0) / (90378);
  const double kGravityComp = 0.058;
  bool oneShot = false;

  double logOffset;
};
