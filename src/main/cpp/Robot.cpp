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
  IO.wrist.ResetEnc();
  IO.vision.Init();
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

  bool btnBackDr = IO.ds.DriverPS.GetScreenShotButton();

  if (IO.ds.chooseController.GetSelected() == IO.ds.sXBX)
  {
    btnBackDr = IO.ds.DriverXB.GetBackButton();
  }

  // IO.vision.CVMode(btnBackDr);
  // AutoTarget(btnBackDr);a\

  UpdateSD();
}

void Robot::AutonomousInit()
{
  IO.drivebase.ResetEncoders();
  IO.drivebase.ResetGyro();
  autoPrograms.Init();
}

void Robot::AutonomousPeriodic()
{
  autoPrograms.Run();
}

void Robot::TeleopInit()
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
  SmartDashboard::PutNumber("rotate1", rotate);
  forward = Deadband(forward, deadband);
  rotate = Deadband(rotate, deadband);
  leftOpY = Deadband(leftOpY, deadband);
  rightOpY = Deadband(rightOpY, deadband);

  //Scaling
  leftOpY *= -1;
  //rotate *= 0.8;

  //
  // Driver
  //
  IO.drivebase.Arcade(forward, rotate);
  
  if (leftBumpDr || leftBumpOp)
  {
    IO.cargoManip.Set(-1.0);
  }

  if (rightBumpDr || rightBumpOp)
  {
    IO.cargoManip.Set(0.5);
    IO.wrist.SetAngle(45);
    IO.elevator.SetPosition(5);
  }

  if (btnStartDr)
  {
    //sensor enable
  }

  if (btnBackDr)
  {
    //sensor disable
  }

  //
  //Operator
  //
  if (btnPSOp)
  {
    IO.elevator.ToggleGantry();
  }

  IO.frontClimber.Set(rightTrigOp - leftTrigOp);

  if (btnStartOp)
  {
    IO.elevator.ActivateSensorOverride();
    IO.wrist.ActivateSensorOverride();
  }

  if (btnBackOp)
  {
    IO.elevator.DeactivateSensorOverride();
    IO.wrist.DeactivateSensorOverride();
  }

  if (btnBCircleOp) 
  {
    IO.hatchManip.Clamp();
    hatchPresets = true;
  }
  if (btnACrossOp) 
  {
    IO.hatchManip.Unclamp();
    hatchPresets = false;
  }
  if (btnYTriangleOp) 
  {
    IO.elevator.SetPosition(18);
    IO.wrist.SetAngle(0);
    IO.hatchManip.Deploy();
  }
  if (btnXSquareOp) 
  {
    IO.elevator.SetPosition(5);
    IO.wrist.SetAngle(110);
    IO.hatchManip.FloorIntakeDown();
  }


  //Elevator
  IO.elevator.Set(leftOpY);

  //Wrist
  IO.wrist.SetSpeed(-rightOpY);
 
  //Presets
  if (hatchPresets)
  {
    if (btnUpOp)
    {
      //high rocket
      IO.elevator.SetPosition(100); 
      IO.wrist.SetAngle(0);
    }
    if (btnDownOp)
    {
      //middle rocket
      IO.elevator.SetPosition(50); 
      IO.wrist.SetAngle(0);
    }
    if (btnRightOp)
    {
      //low rocket
      IO.elevator.SetPosition(25); 
      IO.wrist.SetAngle(0);
    }
    if (btnLeftOp)
    {
      //cargo ship
      IO.elevator.SetPosition(25);
      IO.wrist.SetAngle(0); 
    }
  }
  else
  {
    if (btnUpOp)
    {
      //high rocket
      IO.elevator.SetPosition(100); 
      IO.wrist.SetAngle(0);
    }
    if (btnDownOp)
    {
      //middle rocket
      IO.elevator.SetPosition(50);
      IO.wrist.SetAngle(0); 
    }
    if (btnRightOp)
    {
      //low rocket
      IO.elevator.SetPosition(25); 
      IO.wrist.SetAngle(0);
    }
    if (btnLeftOp)
    {
      //cargo ship
      IO.elevator.SetPosition(40); 
      IO.wrist.SetAngle(30);
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
  else
  {
    return input;
  }
}

void Robot::UpdateSD()
{
  IO.drivebase.UpdateSmartdash();
  IO.elevator.UpdateSmartdash();
  IO.wrist.UpdateSmartdash();
  IO.cargoIntake.UpdateSmartdash();
  IO.cargoManip.UpdateSmartdash();
  IO.hatchManip.UpdateSmartdash();
  IO.frontClimber.UpdateSmartdash();
  autoPrograms.SmartDash();
  IO.ds.SmartDash();
}

bool Robot::AutoTarget(bool Go)
{
  Vision::returnData dataDrop = IO.vision.Run();
  double error = dataDrop.cmd;

  if (Go)
  {
    if (dataDrop.distance >= 70 || error == -3.14)
    {
      IO.drivebase.Arcade(0, 0);
    }
    else
    {
      IO.drivebase.Arcade(0.15, -error);
    }
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
