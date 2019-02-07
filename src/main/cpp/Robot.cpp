/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.hpp"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit()
{
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
  UpdateSD();
}

void Robot::AutonomousInit()
{
  autoPrograms.Init();
}

void Robot::AutonomousPeriodic()
{
  autoPrograms.Run();
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic()
{
  double forward = IO.ds.DriverPS.GetY(GenericHID::kLeftHand);
  double rotate = IO.ds.DriverPS.GetX(GenericHID::kRightHand);
  double strafe = IO.ds.DriverPS.GetX(GenericHID::kLeftHand);
  double forwardR = IO.ds.DriverPS.GetY(GenericHID::kRightHand);
  double leftTrigDr = IO.ds.DriverPS.GetTriggerAxis(GenericHID::kLeftHand);
  double rightTrigDr = IO.ds.DriverPS.GetTriggerAxis(GenericHID::kRightHand); //Negative
  bool leftBumpDr = IO.ds.DriverPS.GetBumper(GenericHID::kLeftHand);
  bool rightBumpDr = IO.ds.DriverPS.GetBumper(GenericHID::kRightHand);
  bool btnDownDr = IO.ds.DriverPS.GetCrossButton();
  bool btnUpDr = IO.ds.DriverPS.GetTriangleButton();
  bool btnRightDr = IO.ds.DriverPS.GetCircleButton();
  bool btnLeftDr = IO.ds.DriverPS.GetSquareButton();

  double leftTrigOp = IO.ds.OperatorPS.GetTriggerAxis(GenericHID::kLeftHand);
  double rightTrigOp = IO.ds.OperatorPS.GetTriggerAxis(GenericHID::kRightHand); //Negative
  bool leftBumpOp = IO.ds.OperatorPS.GetBumper(GenericHID::kLeftHand);
  bool rightBumpOp = IO.ds.OperatorPS.GetBumper(GenericHID::kRightHand);
  bool btnDownOp = IO.ds.OperatorPS.GetCrossButton();
  bool btnUpOp = IO.ds.OperatorPS.GetTriangleButton();
  bool btnRightOp = IO.ds.OperatorPS.GetCircleButton();
  bool btnLeftOp = IO.ds.OperatorPS.GetSquareButton();
  double leftOpY = IO.ds.OperatorPS.GetY(GenericHID::kLeftHand);
  double wristStick = IO.ds.OperatorPS.GetY(GenericHID::kRightHand);

  double OpIntakeCommand = (rightTrigOp - leftTrigOp);

  //Deadbands
  forward = Deadband(forward, deadband);
  rotate = Deadband(rotate, deadband);
  leftOpY = Deadband(leftOpY, deadband);
  wristStick = Deadband(wristStick, deadband);
  OpIntakeCommand = Deadband(OpIntakeCommand, deadband);

  //Scaling
  OpIntakeCommand *= 0.7;
  leftOpY *= -1;

  //Drive
  IO.drivebase.Arcade(forward, rotate);

  if (leftBumpDr)
  {
    IO.drivebase.SetLowGear();
  }

  if (rightBumpDr)
  {
    IO.drivebase.SetHighGear();
  }

  //Elevator
  IO.elevator.Set(leftOpY);

  /*if (btnUpOp == true)  {
    IO.elevator.SetPosition(50);
  }
  if (btnDownOp == true)  {
    IO.elevator.SetPosition(35);
  }
  if (btnLeftOp == true)  {
    IO.elevator.SetPosition(5);
  }*/

  //Wrist
  IO.wrist.Set(-wristStick);

  if (rightBumpOp) 
  {
    IO.wrist.SetAngle(0);
  }
  // if (leftBumpOp == true) 
  // {
  //   IO.wrist.SetAngle(90);
  // }

  //Cargo Manip
  IO.cargoManip.Set(OpIntakeCommand);

  //Cargo Intake
  //IO.cargoIntake.Set();

  //Hatch Manip
  if (btnUpOp) {
    IO.hatchManip.Clamp();
  }
  if (btnRightOp) {
    IO.hatchManip.Unclamp();
  }
  if (btnLeftOp) {
    IO.hatchManip.Eject();
  }
  if (btnDownOp) {
    IO.hatchManip.Retract();
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
  autoPrograms.SmartDash();
  IO.ds.SmartDash();
  SmartDashboard::PutNumber("ANGLE", IO.wrist.GetAngle());
}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
