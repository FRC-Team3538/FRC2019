/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <iostream>

#include <frc/smartdashboard/SmartDashboard.h>

void Robot::RobotInit() {
  motorLeft1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0);
  motorLeft1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_3_Quadrature, 18);

  motorRight1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0);
  motorRight1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_3_Quadrature, 18);

  motorLeft1.SetSelectedSensorPosition(0);
  motorRight1.SetSelectedSensorPosition(0);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

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
void Robot::AutonomousInit() {
}

void Robot::AutonomousPeriodic() {
}

void Robot::TeleopInit() {
    const int currentLim = 20;

    motorLeft1.ConfigFactoryDefault();
    motorLeft2.ConfigFactoryDefault();
    motorRight1.ConfigFactoryDefault();
    motorRight2.ConfigFactoryDefault();

    motorLeft1.SetInverted(true);
    motorLeft2.SetInverted(true);

    motorLeft1.ConfigPeakCurrentLimit(0);
    motorRight1.ConfigPeakCurrentLimit(0);
    motorLeft2.ConfigPeakCurrentLimit(0);
    motorRight2.ConfigPeakCurrentLimit(0);

    motorLeft1.ConfigContinuousCurrentLimit(currentLim);
    motorRight1.ConfigContinuousCurrentLimit(currentLim);
    motorLeft2.ConfigContinuousCurrentLimit(currentLim);
    motorRight2.ConfigContinuousCurrentLimit(currentLim);

    bool useCL = false;
    motorLeft1.EnableCurrentLimit(useCL);
    motorLeft2.EnableCurrentLimit(useCL);
    motorRight1.EnableCurrentLimit(useCL);
    motorRight2.EnableCurrentLimit(useCL);

    motorRight1.ConfigOpenloopRamp(0.2);
    motorLeft1.ConfigOpenloopRamp(0.2);
    motorRight2.ConfigOpenloopRamp(0.2);
    motorLeft2.ConfigOpenloopRamp(0.2);

    motorRight1.SetNeutralMode(motorcontrol::NeutralMode::Brake);
    motorLeft1.SetNeutralMode(motorcontrol::NeutralMode::Brake);
    motorRight2.SetNeutralMode(motorcontrol::NeutralMode::Brake);
    motorLeft2.SetNeutralMode(motorcontrol::NeutralMode::Brake);

    motorLeft1.SetSensorPhase(false);
    motorLeft2.SetSensorPhase(false);
    motorRight1.SetSensorPhase(false);
    motorRight2.SetSensorPhase(false);

    logging.AddKey("Time (s)");
    logging.AddKey("L1 Temp");
    logging.AddKey("L2 Temp");
    logging.AddKey("R1 Temp");
    logging.AddKey("R2 Temp");
    logging.AddKey("L1 Current");
    logging.AddKey("L2 Current");
    logging.AddKey("R1 Current");
    logging.AddKey("R2 Current");
    logging.AddKey("L1 PDPCurrent");
    logging.AddKey("L2 PDPCurrent");
    logging.AddKey("R1 PDPCurrent");
    logging.AddKey("R2 PDPCurrent");
    logging.AddKey("L1 Velocity");
    logging.AddKey("R1 Velocity");
    logging.AddKey("L2 Velocity");
    logging.AddKey("R2 Velocity");
    logging.Start();
    autoLog.Reset();
    autoLog.Start();
    logOffset = autoLog.Get();
}

void Robot::TeleopPeriodic() {
    double forward = DriverPS.GetY(GenericHID::kLeftHand) * -1;
    double rotate = DriverPS.GetX(GenericHID::kRightHand) * -1;
    forward = Deadband(forward, 0.05);
    rotate = Deadband(rotate, 0.05);
    Arcade(forward, rotate);

    EncL = motorLeft1.GetSelectedSensorPosition(0) * kScaleFactor;
    EncR = motorRight1.GetSelectedSensorPosition(0) * kScaleFactor;
    EncL2 = motorLeft2.GetSelectedSensorPosition(0) * kScaleFactor;
    EncR2 = motorRight2.GetSelectedSensorPosition(0) * kScaleFactor;

    logging.Log("Time (s)", std::to_string((autoLog.Get()) - logOffset));
    logging.Log("L1 Temp", std::to_string(motorLeft1.GetTemperature()));
    logging.Log("L2 Temp", std::to_string(motorLeft2.GetTemperature()));
    logging.Log("R1 Temp", std::to_string(motorRight1.GetTemperature()));
    logging.Log("R2 Temp", std::to_string(motorRight2.GetTemperature()));
    logging.Log("L1 Current", std::to_string(motorLeft1.GetOutputCurrent()));
    logging.Log("L2 Current", std::to_string(motorLeft2.GetOutputCurrent()));
    logging.Log("R1 Current", std::to_string(motorRight1.GetOutputCurrent()));
    logging.Log("R2 Current", std::to_string(motorRight2.GetOutputCurrent()));
    logging.Log("L1 PDPCurrent", std::to_string(pdp->GetCurrent(12)));
    logging.Log("L2 PDPCurrent", std::to_string(pdp->GetCurrent(13)));
    logging.Log("R1 PDPCurrent", std::to_string(pdp->GetCurrent(0)));
    logging.Log("R2 PDPCurrent", std::to_string(pdp->GetCurrent(15))); 
    logging.Log("L1 Velocity", std::to_string((((10.0/12.0)*motorLeft1.GetSelectedSensorVelocity(0)*kScaleFactor))));
    logging.Log("L2 Velocity", std::to_string((((10.0/12.0)*motorLeft2.GetSelectedSensorVelocity(0)*kScaleFactor))));
    logging.Log("R1 Velocity", std::to_string((((10.0/12.0)*motorRight1.GetSelectedSensorVelocity(0)*kScaleFactor))));
    logging.Log("R2 Velocity", std::to_string((((10.0/12.0)*motorRight2.GetSelectedSensorVelocity(0)*kScaleFactor))));
    logging.Commit();

    PrevEncL = EncL;
    PrevEncR = EncR;
    PrevEncL2 = EncL2;
    PrevEncR2 = EncR2;
    PrevTime = autoLog.Get();
}

void Robot::TestPeriodic() {}

void Robot::DisabledPeriodic(){
    motorRight1.SetNeutralMode(motorcontrol::NeutralMode::Coast);
    motorLeft1.SetNeutralMode(motorcontrol::NeutralMode::Coast);
    motorRight2.SetNeutralMode(motorcontrol::NeutralMode::Coast);
    motorLeft2.SetNeutralMode(motorcontrol::NeutralMode::Coast);
}


void Robot::Arcade(double forward, double rotate){
    if (std::abs(forward) > 1.0)
    {
        forward /= std::abs(forward);
    }
    if (std::abs(rotate) > 1.0)
    {
        rotate /= std::abs(rotate);
    }
    double l = forward - rotate;
    double r = forward + rotate;

    // Power Limit Test
    double lim = 1;
    l = l>lim?lim:l;
    l = l<-lim?-lim:l;
    r = r>lim?lim:r;
    r = r<-lim?-lim:r;
    

    motorLeft1.Set(l);
    motorRight1.Set(r);
    motorLeft2.Set(l);
    motorRight2.Set(r);
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
int main() { return frc::StartRobot<Robot>(); }
#endif
