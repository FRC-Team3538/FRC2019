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

  WPI_TalonSRX motorLeft1{0};
  WPI_TalonSRX motorLeft2{1};

  WPI_TalonSRX motorRight1{3};
  WPI_TalonSRX motorRight2{4};

  void Arcade(double forward, double rotate);
  double Deadband(double input, double deadband);

  PS4Controller DriverPS{0};

  Logging logging;
  Timer autoLog;
  PowerDistributionPanel *pdp = new PowerDistributionPanel();

  const double kScaleFactor = ((297.5)/(269844.984));
  double EncL;
  double EncR;
  double PrevEncL = 0;
  double PrevEncR = 0;
  double EncL2;
  double EncR2;
  double PrevEncL2 = 0;
  double PrevEncR2 = 0;
  double PrevTime = 0;
  double logOffset;
};
