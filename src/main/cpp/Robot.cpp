/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <TimedRobot.h>
#include <Timer.h>
#include "robotmap.h"

class Robot : public frc::TimedRobot
{
private:
  Timer autoTimer;
  robotmap IO;
  const double deadband = 0.05;
  const int driveTypes = 3;
  int driveMode = 0;

public:
  Robot()
  {
    autoTimer.Start();
  }

  void RobotInit() override
  {
    this->SetPeriod(.020);
  }
  void RobotPeriodic() override
  {
    UpdateSD();

    bool btnOptDrPrsd = IO.ds.DriverPS.GetOptionsButtonPressed();
    //Drive Swapping
    if (btnOptDrPrsd)
    {
      driveMode++;
    }
    if (driveMode == 3)
    {
      driveMode = 0;
    }
  }

  void AutonomousInit() override
  {
    autoTimer.Reset();
    autoTimer.Start();
  }

  void AutonomousPeriodic() override
  {
    // Drive for 2 seconds
    if (autoTimer.Get() < 2.0)
    {
      // Drive forwards half speed
      IO.drivebase.Arcade(0.5, 0.0);
    }
    else
    {
      // Stop robot
      IO.drivebase.Stop();
    }
  }

  void TeleopInit() override {}

  void TeleopPeriodic() override
  {
    double forward = IO.ds.DriverPS.GetY(GenericHID::kLeftHand);
    double rotate = IO.ds.DriverPS.GetX(GenericHID::kRightHand);
    double strafe = IO.ds.DriverPS.GetX(GenericHID::kLeftHand);
    double forwardR = IO.ds.DriverPS.GetY(GenericHID::kRightHand);
    double leftTrigDr = IO.ds.DriverPS.GetTriggerAxis(GenericHID::kLeftHand);
    double rightTrigDr = IO.ds.DriverPS.GetTriggerAxis(GenericHID::kRightHand); //Negative
    bool leftBumpDr = IO.ds.DriverPS.GetBumper(GenericHID::kLeftHand);
    bool rightBumpDr = IO.ds.DriverPS.GetBumper(GenericHID::kRightHand);
    bool btnDownDrPrsd = IO.ds.DriverPS.GetCrossButtonPressed();
    bool btnUpDrPrsd = IO.ds.DriverPS.GetTriangleButtonPressed();
    bool btnRightDrPrsd = IO.ds.DriverPS.GetCircleButtonPressed();
    bool btnLeftDr = IO.ds.DriverPS.GetSquareButton();

    double leftTrigOp = IO.ds.OperatorPS.GetTriggerAxis(GenericHID::kLeftHand);
    double rightTrigOp = IO.ds.OperatorPS.GetTriggerAxis(GenericHID::kRightHand); //Negative
    bool leftBumpOp = IO.ds.OperatorPS.GetBumper(GenericHID::kLeftHand);
    bool rightBumpOp = IO.ds.OperatorPS.GetBumper(GenericHID::kRightHand);
    bool btnDownOpPrsd = IO.ds.OperatorPS.GetCrossButtonPressed();
    bool btnUpOpPrsd = IO.ds.OperatorPS.GetTriangleButtonPressed();
    bool btnRightOpPrsd = IO.ds.OperatorPS.GetCircleButtonPressed();
    bool btnLeftOp = IO.ds.OperatorPS.GetSquareButton();

    //Deadbands
    forward = Deadband(forward, deadband);
    rotate = Deadband(rotate, deadband);
    strafe = Deadband(strafe, deadband);
    forwardR = Deadband(forwardR, deadband);

    //Drive
    if (driveMode == 0)
    {
      IO.drivebase.Arcade(forward, rotate);
    }
    else if (driveMode == 1)
    {
      IO.drivebase.Tank(forward, forwardR);
    }
    else
    {
      IO.drivebase.Holonomic(forward, rotate, strafe);
    }

    if (leftBumpDr)
    {
      IO.drivebase.SetLowGear();
    }

    if (rightBumpDr)
    {
      IO.drivebase.SetHighGear();
    }

    IO.intake.Set(leftTrigDr + rightTrigDr);

    if (btnLeftDr || btnLeftOp)
    {
      IO.intake.Deploy();
    }
    else
    {
      IO.intake.Retract();
    }

    if (btnUpDrPrsd || btnUpOpPrsd)
    {
      IO.intake.SolenoidToggle();
    }

    if (btnDownDrPrsd || btnDownOpPrsd)
    {
      IO.manipB.Forward();
    }

    if (btnRightDrPrsd || btnRightOpPrsd)
    {
      IO.manipB.Stop();
    }
  }

  void TestPeriodic() override {}

private:
  double Deadband(double input, double deadband)
  {
    if ((std::abs(input)) < deadband)
    {
      return 0.0;
    }
    else
    {
      return input;
    }
  }

  void UpdateSD()
  {
    std::string dm = "DriveMode";

    IO.drivebase.LogDriveOutputs();
    IO.drivebase.LogEncoders();

    switch (driveMode)
    {
    case 0:
      SmartDashboard::PutString(dm, "Arcade");
      break;

    case 1:
      SmartDashboard::PutString(dm, "TankyTank");
      break;

    case 2:
      SmartDashboard::PutString(dm, "Holonomic");
      break;
    }

  }
};

START_ROBOT_CLASS(Robot)
