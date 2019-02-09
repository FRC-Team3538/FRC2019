#include "subsystem/Drivebase.hpp"

#include <frc/smartdashboard/SmartDashboard.h>

Drivebase::Drivebase()
{
    motorLeft1.ConfigFactoryDefault();
    motorLeft2.ConfigFactoryDefault();
    motorLeft3.ConfigFactoryDefault();
    motorRight1.ConfigFactoryDefault();
    motorRight2.ConfigFactoryDefault();
    motorRight3.ConfigFactoryDefault();

    motorLeft1.OverrideLimitSwitchesEnable(false);
    motorRight1.OverrideLimitSwitchesEnable(false);

    // set default shifter state
    solenoidShifter.Set(false);

    // Invert one side of the drive
    motorLeft1.SetInverted(true);
    motorLeft2.SetInverted(true);
    motorLeft3.SetInverted(true);

    motorRight1.SetInverted(false);
    motorRight2.SetInverted(false);
    motorRight3.SetInverted(false);

    // master > slaves
    motorLeft2.Follow(motorLeft1);
    motorLeft3.Follow(motorLeft1);

    motorRight2.Follow(motorRight1);
    motorRight3.Follow(motorRight1);

    // Encoder Feedback
    motorLeft1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder);
    motorLeft1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_3_Quadrature, 18);

    motorRight1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder);
    motorRight1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_3_Quadrature, 18);

    // motorLeft1.ConfigSelectedFeedbackCoefficient(-1.0);
    // motorRight1.ConfigSelectedFeedbackCoefficient(1.0);

    motorLeft1.SetSensorPhase(true);
    motorRight1.SetSensorPhase(true);
}

// Arcade Drive
void Drivebase::Arcade(double forward, double turn)
{
    motorLeft1.Set(forward - turn);
    motorRight1.Set(forward + turn);
}

// Stop!
void Drivebase::Stop()
{
    motorLeft1.StopMotor();
    motorRight1.StopMotor();
}

// Shift to High Gear
void Drivebase::SetHighGear()
{
    solenoidShifter.Set(true);
}

// Shift to Low Gear
void Drivebase::SetLowGear()
{
    solenoidShifter.Set(false);
}

// Reset Encoders
void Drivebase::ResetEncoders()
{
    motorLeft1.SetSelectedSensorPosition(0);
    motorRight1.SetSelectedSensorPosition(0);
}

double Drivebase::GetEncoderPositionLeft()
{
    return motorLeft1.GetSelectedSensorPosition(0) * kScaleFactor;
}

double Drivebase::GetEncoderPositionRight()
{
    return motorRight1.GetSelectedSensorPosition(0) * kScaleFactor;
}

// Gyro
void Drivebase::ResetGyro()
{
    navx.ZeroYaw();
}

double Drivebase::GetGyroHeading()
{
    return navx.GetFusedHeading();
}

// SmartDash updater
void Drivebase::UpdateSmartdash()
{
    SmartDashboard::PutNumber("DriveL", motorLeft1.Get());
    SmartDashboard::PutNumber("DriveR", motorRight1.Get());

    SmartDashboard::PutNumber("DriveEncL", GetEncoderPositionLeft());
    SmartDashboard::PutNumber("DriveEncR", GetEncoderPositionRight());

    SmartDashboard::PutBoolean("DriveShifter", solenoidShifter.Get());

    SmartDashboard::PutNumber("GyroFused", GetGyroHeading());
}