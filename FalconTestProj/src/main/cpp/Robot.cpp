/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

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
  SmartDashboard::PutNumber("Elev Enc", Elev.GetSelectedSensorPosition(0) * kScaleFactor);
  SmartDashboard::PutNumber("Elev Temp", Elev.GetTemperature());
}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit()
{
}

void Robot::AutonomousPeriodic()
{
}

void Robot::TeleopInit()
{
  const int currentLim = 20;

  Elev.ConfigFactoryDefault();

  Elev.ConfigPeakCurrentLimit(0);

  Elev.ConfigContinuousCurrentLimit(currentLim);
  bool useCL = false;
  Elev.EnableCurrentLimit(useCL);

  Elev.SetNeutralMode(motorcontrol::NeutralMode::Brake);

  Elev.SetInverted(true);
  Elev.SetSensorPhase(false);

  Elev.ConfigOpenloopRamp(0.0); //0.3

  Elev.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder);
  Elev.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_3_Quadrature, 18);

  int absolutePosition = Elev.GetSelectedSensorPosition(0) & 0xFFF;

  Elev.SetSelectedSensorPosition(absolutePosition);

  int kPIDLoopIdx = 0;
  int kTimeoutMs = 30;

  Elev.Config_kF(kPIDLoopIdx, 0.0);
  Elev.Config_kP(kPIDLoopIdx, 0.18);  //0.15  0.125
  Elev.Config_kI(kPIDLoopIdx, 0.000); // 0.0005
  Elev.Config_kD(kPIDLoopIdx, 14);     //-1.0

  Elev.ConfigNominalOutputForward(0);
  Elev.ConfigNominalOutputReverse(0);
  Elev.ConfigPeakOutputForward(1);
  Elev.ConfigPeakOutputReverse(-0.5);

  // Elev.ConfigAllowableClosedloopError(kPIDLoopIdx, 91.375);
  // Elev.Config_IntegralZone(kPIDLoopIdx, 548.25);

  Elev.ConfigClearPositionOnLimitR(true);

  logging.AddKey("Time (s)");
  logging.AddKey("Elev Temp");
  logging.AddKey("Elev Current");
  logging.AddKey("Elev PDPCurrent");
  logging.AddKey("Elev Velocity");
  logging.Start();
  autoLog.Reset();
  autoLog.Start();
}

void Robot::TeleopPeriodic()
{

  if(!oneShot){
    logOffset = autoLog.Get();
    oneShot = true;
  }

  logging.Log("Time (s)", std::to_string((autoLog.Get()) - logOffset));
  logging.Log("Elev Temp", std::to_string(Elev.GetTemperature()));
  logging.Log("Elev Current", std::to_string(Elev.GetOutputCurrent()));
  logging.Log("Elev PDPCurrent", std::to_string(pdp->GetCurrent(15)));
  logging.Log("Elev Velocity", std::to_string((((10.0 / 12.0) * Elev.GetSelectedSensorVelocity(0) * kScaleFactor))));
  logging.Commit();

  double forward = OperatorPS.GetY(GenericHID::kLeftHand) * -1;
  bool down = OperatorPS.GetDownButton();
  bool left = OperatorPS.GetLeftButton();
  bool up = OperatorPS.GetUpButton();
  forward = Deadband(forward, 0.05);
  if (down)
  {
    SetPosition(11);
  }
  else if(left)
  {
    SetPosition(42);
  }
  else if(up)
  {
    SetPosition(64);
  }
  else
  {
    Set(forward);
  }
  SmartDashboard::PutNumber("Op Joy L Y", forward);
}

void Robot::TestPeriodic() {}

void Robot::DisabledPeriodic()
{
  Elev.SetNeutralMode(motorcontrol::NeutralMode::Brake);
}

void Robot::Set(double speed)
{
  Elev.Set(ControlMode::PercentOutput, speed, DemandType::DemandType_ArbitraryFeedForward, kGravityComp);
}

void Robot::SetPosition(double pos)
{
  Elev.Set(ControlMode::Position, pos / kScaleFactor, DemandType::DemandType_ArbitraryFeedForward, kGravityComp);
}

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

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
