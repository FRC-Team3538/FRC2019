/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <Timer.h>
#include <SmartDashboard/SmartDashboard.h>

#include "robotmap.h"
#include "PS4Controller.h"

class Robot : public frc::TimedRobot {
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
      IO.drivebase.Arcade(0.5, 0.0);
    } else {
      // Stop robot
      IO.drivebase.Stop();
    }
  }

  void TeleopInit() override {}

  void TeleopPeriodic() override {
    // Drive with arcade style (use right stick)
    IO.drivebase.Arcade(m_stick.GetY(GenericHID::JoystickHand::kLeftHand), m_stick.GetX(GenericHID::JoystickHand::kRightHand));    
    SmartDashboard::PutBoolean("Cross Button", m_stick.GetCrossButton());
    SmartDashboard::PutBoolean("Square Button", m_stick.GetSquareButton());
    SmartDashboard::PutBoolean("Circle Button", m_stick.GetCircleButton());
    SmartDashboard::PutBoolean("Triangle Button", m_stick.GetTriangleButton());
    SmartDashboard::PutBoolean("ScreenShot Button", m_stick.GetScreenShotButton());
    SmartDashboard::PutBoolean("Options Button", m_stick.GetOptionsButton());
    SmartDashboard::PutBoolean("PS Button", m_stick.GetPSButton());
    SmartDashboard::PutBoolean("TouchPad Button", m_stick.GetTouchPadButton());
    SmartDashboard::PutNumber("Left Trigger", m_stick.GetTriggerAxis(GenericHID::JoystickHand::kLeftHand));
    SmartDashboard::PutNumber("Right Trigger", m_stick.GetTriggerAxis(GenericHID::JoystickHand::kRightHand));
    SmartDashboard::PutBoolean("Left Bumper Button", m_stick.GetBumper(GenericHID::JoystickHand::kLeftHand));
    SmartDashboard::PutBoolean("Right Bumper Button", m_stick.GetBumper(GenericHID::JoystickHand::kRightHand));
    SmartDashboard::PutBoolean("Left Stick Button", m_stick.GetStickButton(GenericHID::JoystickHand::kLeftHand));
    SmartDashboard::PutBoolean("Right Stick Button", m_stick.GetStickButton(GenericHID::JoystickHand::kRightHand));
    SmartDashboard::PutNumber("POV", m_stick.GetPOV(0));
    SmartDashboard::PutBoolean("Up Button", m_stick.GetUPButton());
    SmartDashboard::PutBoolean("Right Button", m_stick.GetRightButton());
    SmartDashboard::PutBoolean("Down Button", m_stick.GetDownButton());
    SmartDashboard::PutBoolean("Left Button", m_stick.GetLeftButton());
  }

  void TestPeriodic() override {}

 private:
  PS4Controller m_stick{0};
  LiveWindow& m_lw = *frc::LiveWindow::GetInstance();
  Timer m_timer;

  robotmap IO;
};

START_ROBOT_CLASS(Robot)
