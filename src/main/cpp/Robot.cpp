/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <IterativeRobot.h>
#include <Joystick.h>
#include <LiveWindow/LiveWindow.h>
#include <Timer.h>

#include "robotmap.h"

class Robot : public frc::IterativeRobot {
 public:
  Robot() {
    m_timer.Start();
  }

  void AutonomousInit() override {
    m_timer.Reset();
    m_timer.Start();
  }

  void AutonomousPeriodic() override {
    // Drive for 2 seconds
    if (m_timer.Get() < 2.0) {
      // Drive forwards half speed
      IO.driveBase.ArcadeDrive(0.5, 0.0);
    } else {
      // Stop robot
      IO.driveBase.ArcadeDrive(0.0, 0.0);
    }
  }

  void TeleopInit() override {}

  void TeleopPeriodic() override {
    // Drive with arcade style (use right stick)
    IO.driveBase.ArcadeDrive(m_stick.GetY(), m_stick.GetX());
  }

  void TestPeriodic() override {}

 private:
  frc::Joystick m_stick{0};
  frc::LiveWindow& m_lw = *frc::LiveWindow::GetInstance();
  frc::Timer m_timer;

  robotmap IO;
};

START_ROBOT_CLASS(Robot)
