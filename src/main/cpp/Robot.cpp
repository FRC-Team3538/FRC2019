/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <TimedRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SmartDashboard.h>

#include "robotmap.h"
#include "auto/AutoPrograms.h"

class Robot : public frc::TimedRobot
{
private:
  robotmap IO;
  AutoPrograms autoPrograms{IO};
  LiveWindow &m_lw = *frc::LiveWindow::GetInstance();

  const double deadband = 0.05;

  enum driveModes
  {
    ARCADE,
    TANKYTANK,
    HOLONOMIC
  };
  int driveMode = driveModes::ARCADE;

public:

  /*************************************************
   *                    Robot                      *
   *************************************************/

  void RobotInit() override
  {
    this->SetPeriod(.020);
  }

  void RobotPeriodic() override
  {
    UpdateSD();

    bool btnOptDrPrsd = IO.ds.DriverPS.GetOptionsButtonPressed();
    if(IO.ds.chooseController.GetSelected() == IO.ds.sXBX){
      btnOptDrPrsd = IO.ds.DriverXB.GetStartButtonPressed();
    }
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

  /*************************************************
   *                    Teleop                     *
   *************************************************/

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
    frc::SmartDashboard::PutNumber("Forward0", forward);

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
      btnDownDrPrsd = IO.ds.DriverXB.GetAButtonPressed();
      btnUpDrPrsd = IO.ds.DriverXB.GetYButtonPressed();
      btnRightDrPrsd = IO.ds.DriverXB.GetBButtonPressed();
      btnLeftDr = IO.ds.DriverXB.GetXButton();
      frc::SmartDashboard::PutNumber("Forward1", forward);

      leftTrigOp = IO.ds.OperatorXB.GetTriggerAxis(GenericHID::kLeftHand);
      rightTrigOp = IO.ds.OperatorXB.GetTriggerAxis(GenericHID::kRightHand); //Negative
      leftBumpOp = IO.ds.OperatorXB.GetBumper(GenericHID::kLeftHand);
      rightBumpOp = IO.ds.OperatorXB.GetBumper(GenericHID::kRightHand);
      btnDownOpPrsd = IO.ds.OperatorXB.GetAButtonPressed();
      btnUpOpPrsd = IO.ds.OperatorXB.GetYButtonPressed();
      btnRightOpPrsd = IO.ds.OperatorXB.GetBButtonPressed();
      btnLeftOp = IO.ds.OperatorXB.GetXButton();
    }

    //Deadbands
    forward = Deadband(forward, deadband);
    rotate = Deadband(rotate, deadband);
    strafe = Deadband(strafe, deadband);
    forwardR = Deadband(forwardR, deadband);

    //Drive
    switch (driveMode)
    {
    case driveModes::ARCADE:
      IO.drivebase.Arcade(forward, rotate);
      break;

    case driveModes::TANKYTANK:
      IO.drivebase.Tank(forward, forwardR);
      break;

    case driveModes::HOLONOMIC:
      IO.drivebase.Holonomic(forward, rotate, strafe);
      break;
    }

    if (leftBumpDr)
    {
      IO.drivebase.SetLowGear();
    }

    if (rightBumpDr)
    {
      IO.drivebase.SetHighGear();
    }

    IO.intake.Set(leftTrigDr + rightTrigDr + leftTrigOp + rightTrigOp);

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
      IO.manipB.SolenoidToggle();
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

  /*************************************************
   *               Auto No Mouse!                  *
   *************************************************/

  void AutonomousInit() override
  {
    autoPrograms.Init();
  }

  void AutonomousPeriodic() override
  {
    autoPrograms.Run();
  }


  /*************************************************
   *              Helper Functions                 *
   *************************************************/
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

    IO.drivebase.UpdateSmartdash();
    IO.intake.UpdateSmartdash();
    IO.manipB.UpdateSmartdash();
  }


};
START_ROBOT_CLASS(Robot)
