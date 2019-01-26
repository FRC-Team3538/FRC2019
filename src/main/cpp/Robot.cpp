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
  double rightOpY = IO.ds.OperatorPS.GetY(GenericHID::kRightHand);
  double wristStick = IO.ds.OperatorPS.GetX(GenericHID::kLeftHand);

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
    btnDownDr = IO.ds.DriverXB.GetAButton();
    btnUpDr = IO.ds.DriverXB.GetYButton();
    btnRightDr = IO.ds.DriverXB.GetBButton();
    btnLeftDr = IO.ds.DriverXB.GetXButton();

    leftTrigOp = IO.ds.OperatorXB.GetTriggerAxis(GenericHID::kLeftHand);
    rightTrigOp = IO.ds.OperatorXB.GetTriggerAxis(GenericHID::kRightHand); //Negative
    leftBumpOp = IO.ds.OperatorXB.GetBumper(GenericHID::kLeftHand);
    rightBumpOp = IO.ds.OperatorXB.GetBumper(GenericHID::kRightHand);
    btnDownOp = IO.ds.OperatorXB.GetAButton();
    btnUpOp = IO.ds.OperatorXB.GetYButton();
    btnRightOp = IO.ds.OperatorXB.GetBButton();
    btnLeftOp = IO.ds.OperatorXB.GetXButton();
    rightOpY = IO.ds.OperatorXB.GetY(GenericHID::kRightHand);
    wristStick = IO.ds.OperatorXB.GetX(GenericHID::kLeftHand);
  };

  double OpIntakeCommand = (rightTrigOp - leftTrigOp);

  //Deadbands
  forward = Deadband(forward, deadband);
  rotate = Deadband(rotate, deadband);
  rightOpY = Deadband(rightOpY, deadband);
  wristStick = Deadband(wristStick, deadband);
  OpIntakeCommand = Deadband(OpIntakeCommand, deadband) * 0.7;

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
  IO.elevator.Set(-rightOpY);

  if (btnUpOp)
  {
    IO.elevator.resetEnc();
  }
  //Wrist
  IO.wrist.Set(wristStick);

  //Claw
  if (rightBumpOp or (rightTrigOp > 0.125)) {
			// Loose Intake
			IO.claw.Compliant(); // Compliant
			IO.claw.Set(1.0);

		} else if (leftBumpOp) {
			// Drop it like it's hot
			IO.claw.Open(); // Open
			IO.claw.Set(0.0);

		} else if (btnRightOp) {
			IO.claw.Close(); // Closed
			IO.claw.Set(1.0); // Intake
		}
		else if (rightTrigDr > 0.75) {
			// Loose Intake [Driver]
			IO.claw.Close(); // Closed
			IO.claw.Set(-0.7);

		} else if (rightTrigDr > 0.15) {
			// Loose Intake [Driver]
			IO.claw.Close(); // Closed
			IO.claw.Set(-0.3);

		} else if (leftTrigDr > 0.25) {
			// Drop it like it's hot
			IO.claw.Open(); // Open
			IO.claw.Set(0.0);

		}
		else {
			// Default Hold Cube, cube eject routes through here as well
			IO.claw.Close(); // Closed
			IO.claw.Set(OpIntakeCommand);
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
  std::string dm = "DriveMode";

  IO.drivebase.UpdateSmartdash();
  IO.elevator.UpdateSmartdash();
  IO.claw.UpdateSmartdash();
  IO.wrist.UpdateSmartdash();
  autoPrograms.SmartDash();
  IO.ds.SmartDash();
}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
