/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.hpp"
#include <iostream>
#include <frc/Threads.h>
#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit()
{
  IO.elevator.ResetEnc();
  IO.drivebase.ResetEncoders();
  IO.drivebase.ResetGyro();
  IO.vision.Init();
  IO.wrist.ResetEnc();
  IO.elevator.SetServo(IO.elevator.servoSetPoints::min);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic()
{
  // Zero Switches
  if (IO.elevator.GetElvSwitchLower())
  {
    IO.elevator.ResetEnc();
  }

  if (IO.wrist.GetSwitchUpper())
  {
    IO.wrist.ResetEnc();
  }

  //
  // Sensor Override
  //
  bool btnBackOp = IO.ds.OperatorPS.GetScreenShotButton();
  bool btnStartOp = IO.ds.OperatorPS.GetOptionsButton();

  if (IO.ds.chooseController.GetSelected() == IO.ds.sXBX)
  {
    btnBackOp = IO.ds.OperatorXB.GetBackButton();
    btnStartOp = IO.ds.OperatorXB.GetStartButton();
  }

  // Limits
  if (IO.ds.chooseDriveLimit.GetSelected() == IO.ds.sUnlimitted)
  {
    IO.drivebase.ActivateSensorOverride();
  }
  else
  {
    IO.drivebase.DeactivateSensorOverride();
  }

  if (IO.ds.chooseElevatorLimit.GetSelected() == IO.ds.sUnlimitted)
  {
    IO.elevator.ActivateSensorOverride();
  }
  else
  {
    IO.elevator.DeactivateSensorOverride();
  }

  if (IO.ds.chooseWristLimit.GetSelected() == IO.ds.sUnlimitted)
  {
    IO.wrist.ActivateSensorOverride();

    if (IO.ds.DriverPS.GetPSButton())
    {
      IO.wrist.ResetEnc();
    }
  }
  else if (IO.ds.chooseWristLimit.GetSelected() == IO.ds.sMoreUnlimitted)
  {
    IO.wrist.ActivateLimitSwitchOverride();
    

    if (IO.ds.DriverPS.GetPSButton())
    {
      IO.wrist.ResetEnc();
    }
  }
  else
  {
    IO.wrist.DeactivateSensorOverride();
  }

  // Update Smart Dash
  UpdateSD();
  bool btnACrossDrPrsd = IO.ds.DriverPS.GetCrossButtonPressed();
  if (IO.ds.chooseController.GetSelected() == IO.ds.sXBX)
  {
    btnACrossDrPrsd = IO.ds.DriverXB.GetAButtonPressed();
  }
  if (btnACrossDrPrsd)
  {
    IO.vision.HumanVisionToggle();
  }

  if (IO.elevator.GetDistance() < 0)
  {
    IO.elevator.ResetEnc();
  }
}

void Robot::AutonomousInit()
{
  IO.drivebase.ResetEncoders();
  IO.drivebase.ResetGyro();
  autoPrograms.Init();
}

void Robot::AutonomousPeriodic()
{
  bool btnPSDr = IO.ds.DriverPS.GetPSButtonPressed();

  // if (btnPSDr)
  // {
  stopAuton = true;
  //}

  if (stopAuton)
  {
    TeleopPeriodic();
  }
  else
  {
    autoPrograms.Run();
  }
}

void Robot::TeleopInit()
{
  IO.wrist.SetAngle(IO.wrist.GetAngle());
  IO.elevator.SetPosition(IO.elevator.GetDistance()); //IO.elevator.AGetDistance()
}

void Robot::DisabledInit()
{
}

void Robot::TeleopPeriodic()
{
  double forward = IO.ds.DriverPS.GetY(GenericHID::kLeftHand) * -1;
  double rotate = IO.ds.DriverPS.GetX(GenericHID::kRightHand) * -1;
  double strafe = IO.ds.DriverPS.GetX(GenericHID::kLeftHand);
  double forwardR = IO.ds.DriverPS.GetY(GenericHID::kRightHand);
  double leftTrigDr = IO.ds.DriverPS.GetTriggerAxis(GenericHID::kLeftHand);
  double rightTrigDr = IO.ds.DriverPS.GetTriggerAxis(GenericHID::kRightHand); //Negative
  bool leftBumpDr = IO.ds.DriverPS.GetBumper(GenericHID::kLeftHand);
  bool rightBumpDr = IO.ds.DriverPS.GetBumper(GenericHID::kRightHand);
  bool btnACrossDr = IO.ds.DriverPS.GetCrossButton();
  bool btnYTriangleDr = IO.ds.DriverPS.GetTriangleButton();
  bool btnBCircleDr = IO.ds.DriverPS.GetCircleButton();
  bool btnXSquareDr = IO.ds.DriverPS.GetSquareButton();
  bool btnUpDr = IO.ds.DriverPS.GetUPButton();
  bool btnRightDr = IO.ds.DriverPS.GetRightButton();
  bool btnLeftDr = IO.ds.DriverPS.GetLeftButton();
  bool btnDownDr = IO.ds.DriverPS.GetDownButton();
  bool btnBackDr = IO.ds.DriverPS.GetScreenShotButton();
  bool btnStartDr = IO.ds.DriverPS.GetOptionsButton();
  bool btnPSDr = IO.ds.DriverPS.GetPSButtonPressed();

  double leftTrigOp = IO.ds.OperatorPS.GetTriggerAxis(GenericHID::kLeftHand);
  double rightTrigOp = IO.ds.OperatorPS.GetTriggerAxis(GenericHID::kRightHand); //Negative
  double leftOpY = IO.ds.OperatorPS.GetY(GenericHID::kLeftHand);
  double rightOpY = IO.ds.OperatorPS.GetY(GenericHID::kRightHand);
  bool leftBumpOp = IO.ds.OperatorPS.GetBumper(GenericHID::kLeftHand);
  bool rightBumpOp = IO.ds.OperatorPS.GetBumper(GenericHID::kRightHand);
  bool btnACrossOp = IO.ds.OperatorPS.GetCrossButton();
  bool btnBCircleOp = IO.ds.OperatorPS.GetCircleButton();
  bool btnYTriangleOp = IO.ds.OperatorPS.GetTriangleButton();
  bool btnXSquareOp = IO.ds.OperatorPS.GetSquareButton();
  bool btnUpOp = IO.ds.OperatorPS.GetUPButton();
  bool btnRightOp = IO.ds.OperatorPS.GetRightButton();
  bool btnLeftOp = IO.ds.OperatorPS.GetLeftButton();
  bool btnDownOp = IO.ds.OperatorPS.GetDownButton();
  bool btnBackOp = IO.ds.OperatorPS.GetScreenShotButton();
  bool btnStartOp = IO.ds.OperatorPS.GetOptionsButton();
  bool btnPSOp = IO.ds.OperatorPS.GetPSButtonPressed();

  if (IO.ds.chooseController.GetSelected() == IO.ds.sXBX)
  {
    forward = IO.ds.DriverXB.GetY(GenericHID::kLeftHand);
    rotate = IO.ds.DriverXB.GetX(GenericHID::kRightHand);
    strafe = IO.ds.DriverXB.GetX(GenericHID::kLeftHand);
    forwardR = IO.ds.DriverXB.GetY(GenericHID::kRightHand);
    leftTrigDr = IO.ds.DriverXB.GetTriggerAxis(GenericHID::kLeftHand);
    rightTrigDr = IO.ds.DriverXB.GetTriggerAxis(GenericHID::kRightHand); //Negative
    leftBumpDr = IO.ds.DriverXB.GetBumper(GenericHID::kLeftHand);
    rightBumpDr = IO.ds.DriverXB.GetBumper(GenericHID::kRightHand);
    btnACrossDr = IO.ds.DriverXB.GetAButton();
    btnBCircleDr = IO.ds.DriverXB.GetBButton();
    btnXSquareDr = IO.ds.DriverXB.GetXButton();
    btnYTriangleDr = IO.ds.DriverXB.GetYButton();
    btnUpDr = IO.ds.DriverXB.GetPOV() == 315 || IO.ds.DriverXB.GetPOV() == 0 || IO.ds.DriverXB.GetPOV() == 45;
    btnRightDr = IO.ds.DriverXB.GetPOV() == 45 || IO.ds.DriverXB.GetPOV() == 90 || IO.ds.DriverXB.GetPOV() == 135;
    btnLeftDr = IO.ds.DriverXB.GetPOV() == 225 || IO.ds.DriverXB.GetPOV() == 270 || IO.ds.DriverXB.GetPOV() == 315;
    btnDownDr = IO.ds.DriverXB.GetPOV() == 135 || IO.ds.DriverXB.GetPOV() == 180 || IO.ds.DriverXB.GetPOV() == 225;
    btnBackDr = IO.ds.DriverXB.GetBackButton();
    btnStartDr = IO.ds.DriverXB.GetStartButton();

    leftTrigOp = IO.ds.OperatorXB.GetTriggerAxis(GenericHID::kLeftHand);
    rightTrigOp = IO.ds.OperatorXB.GetTriggerAxis(GenericHID::kRightHand); //Negative
    leftOpY = IO.ds.OperatorXB.GetY(GenericHID::kLeftHand);
    rightOpY = IO.ds.OperatorXB.GetY(GenericHID::kRightHand);
    leftBumpOp = IO.ds.OperatorXB.GetBumper(GenericHID::kLeftHand);
    rightBumpOp = IO.ds.OperatorXB.GetBumper(GenericHID::kRightHand);
    btnYTriangleOp = IO.ds.OperatorXB.GetYButton();
    btnACrossOp = IO.ds.OperatorXB.GetAButton();
    btnBCircleOp = IO.ds.OperatorXB.GetBButton();
    btnXSquareOp = IO.ds.OperatorXB.GetXButton();
    btnUpOp = IO.ds.OperatorXB.GetPOV() == 315 || IO.ds.OperatorXB.GetPOV() == 0 || IO.ds.OperatorXB.GetPOV() == 45;
    btnRightOp = IO.ds.OperatorXB.GetPOV() == 45 || IO.ds.OperatorXB.GetPOV() == 90 || IO.ds.OperatorXB.GetPOV() == 135;
    btnLeftOp = IO.ds.OperatorXB.GetPOV() == 225 || IO.ds.OperatorXB.GetPOV() == 270 || IO.ds.OperatorXB.GetPOV() == 315;
    btnDownOp = IO.ds.OperatorXB.GetPOV() == 135 || IO.ds.OperatorXB.GetPOV() == 180 || IO.ds.OperatorXB.GetPOV() == 225;
    btnBackOp = IO.ds.OperatorXB.GetBackButton();
    btnStartOp = IO.ds.OperatorXB.GetStartButton();
  }

  //Deadbands
  forward = Deadband(forward, deadband);
  rotate = Deadband(rotate, deadband);
  leftOpY = Deadband(leftOpY, deadband);
  rightOpY = Deadband(rightOpY, deadband);

  //Scaling
  leftOpY *= -1;

  if (IO.elevator.GetGantryActivated())
  {
    leftOpY *= 1.0;
  }
  else
  {
    if (!leftOpY == 0)
    {
      leftOpY = (0.2342 * (leftOpY * leftOpY * leftOpY)) + (-0.0689 * (leftOpY * leftOpY)) + (0.4658 * leftOpY) + 0.125;
    }
  }

  //
  // Driver
  //
  // IO.vision.CVMode(btnBCircleDr); ******************
  // AutoTarget(btnBCircleDr, forward); ******************
  if (!btnBCircleDr)
  {
    IO.drivebase.Arcade(forward, rotate);
    // IO.drivebase.testRev.Set(forward);
  }

  // Manip Intake / Eject
  if ((rightTrigDr > 0.05) || leftBumpOp)
  {
    IO.cargoManip.Set(-1.0);
  }
  else if ((leftTrigDr > 0.05) || rightBumpOp)
  {
    IO.cargoManip.Set(1.0);
    IO.wrist.SetAngle(-90);
    //IO.elevator.SetPosition(2);

    IO.hatchManip.FloorIntakeUp();
    IO.hatchManip.Retract();
  }
  else
  {
    IO.cargoManip.Set(0.0);
  }

  //
  //Operator
  //
  if (btnPSOp)
  {
    IO.elevator.ToggleGantry();
  }

  IO.elevator.SetServo(IO.elevator.servoSetPoints::autoSet);

  double frontDeployCMD = rightTrigOp - leftTrigOp;
  if (frontDeployCMD < 0.0)
  {
    IO.elevator.SetPosition(10.0);
    IO.frontClimber.Set(frontDeployCMD * 0.5);
  }
  else
  {
    IO.frontClimber.Set(frontDeployCMD);
  }

  // Hatch Clamp
  if (btnBCircleOp)
  {
    IO.hatchManip.Clamp();
  }

  if (btnACrossOp)
  {
    IO.hatchManip.Unclamp();
  }

  // Hatch Deploy
  if (btnYTriangleOp)
  {
    IO.wrist.SetAngle(0);
    IO.hatchManip.Deploy();
  }

  if (btnXSquareOp)
  {
    IO.hatchManip.Retract();
  }

  //Elevator
  // if((!(leftOpY) > 0) && IO.elevator.GetGantryActivated()){
  //   IO.elevator.LevelRobot(IO.drivebase.GetPitch());
  // }
  //else{
  IO.elevator.Set(leftOpY);
  //}

  //Wrist
  IO.wrist.SetSpeed(rightOpY);
  hatchPresets = IO.hatchManip.Deployed();

  //Presets
  if (hatchPresets)
  {
    // Hatch
    if (btnUpOp)
    {
      // High rocket
      IO.elevator.SetPosition(67);
      IO.wrist.SetAngle(0);
    }
    if (btnLeftOp)
    {
      // Mid Rocket
      IO.elevator.SetPosition(41);
      IO.wrist.SetAngle(0);
    }
    if (btnRightOp)
    {
      // Cargo Ship
      IO.elevator.SetPosition(13);
      IO.wrist.SetAngle(0);
    }
    if (btnDownOp)
    {
      // Low rocket
      IO.elevator.SetPosition(13);
      IO.wrist.SetAngle(0);
    }
  }
  else
  {
    // Cargo
    if (btnUpOp)
    {
      // High rocket
      IO.elevator.SetPosition(65);
      IO.wrist.SetAngle(0);
    }
    if (btnLeftOp)
    {
      // Mid Rocket
      IO.elevator.SetPosition(37);
      IO.wrist.SetAngle(0);
    }
    if (btnRightOp)
    {
      // CargoShip
      IO.elevator.SetPosition(23);

      if (IO.elevator.GetDistance() > 18)
      {
        IO.wrist.SetAngle(-40);
      }
    }
    if (btnDownOp)
    {
      // Low rocket
      IO.elevator.SetPosition(9);
      IO.wrist.SetAngle(0);
    }
  }
}
void Robot::TestPeriodic() {}

double Robot::Deadband(double input, double deadband)
{
  if ((std::abs(input)) < deadband)
  {
    return 0.0;
  }
  else if (input > 0.95)
  {
    return 1.0;
  }
  else if (input < -0.95)
  {
    return -1.0;
  }
  else
  {
    return input;
  }
}

void Robot::UpdateSD()
{
  // Don't update smart dash every loop,
  // it causes watchdog warnings
  if ((smartDashSkip++ < 10))
  {
    return;
  }
  smartDashSkip = 0;

  // Critical
  autoPrograms.SmartDash();
  IO.ds.SmartDash();

  // Optional
  IO.drivebase.UpdateSmartdash();
  IO.elevator.UpdateSmartdash();
  IO.wrist.UpdateSmartdash();
  IO.cargoManip.UpdateSmartdash();
  IO.hatchManip.UpdateSmartdash();
  IO.frontClimber.UpdateSmartdash();
}

bool Robot::AutoTarget(bool Go, double forward)
{
  Vision::returnData dataDrop = IO.vision.Run();
  double error = dataDrop.cmd;

  if (Go)
  {
    if (error == -3.14)
    {
      error = 0;
    }
    IO.drivebase.Arcade(forward, -error);
  }
  if (abs(error) < 0.05)
  {
    return true;
  }
  //std::cout << error << endl;
}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
