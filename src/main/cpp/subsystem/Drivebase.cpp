#include "subsystem/Drivebase.hpp"
#include <frc/smartdashboard/SmartDashboard.h>

Drivebase::Drivebase()
{
    // set default shifter state
    solenoidShifter.Set(false);

    // Invert one side of the drive
    motorLeft1.SetInverted(false);
    motorLeft2.SetInverted(false);
    motorLeft3.SetInverted(false);

    motorRight1.SetInverted(true);
    motorRight2.SetInverted(true);
    motorRight3.SetInverted(true);

    // master > slaves
    motorLeft2.Follow(motorLeft1);
    motorLeft3.Follow(motorLeft1);

    motorRight2.Follow(motorRight1);
    motorRight3.Follow(motorRight1);

    // Encoder Feedback
    motorRight1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder);
    motorRight1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_3_Quadrature, 18);

    motorLeft1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder);
    motorLeft1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_3_Quadrature, 18);
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
    return motorLeft1.GetSensorCollection().GetQuadraturePosition() * kScaleFactor;
}

double Drivebase::GetEncoderPositionRight()
{
    return motorRight1.GetSensorCollection().GetQuadraturePosition() * kScaleFactor;
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

// SmartDash updator
void Drivebase::UpdateSmartdash()
{
    SmartDashboard::PutNumber("DriveL", motorLeft1.Get());
    SmartDashboard::PutNumber("DriveR", motorRight1.Get());

    SmartDashboard::PutNumber("DriveEncL", GetEncoderPositionRight());
    SmartDashboard::PutNumber("DriveEncR", GetEncoderPositionRight());

    SmartDashboard::PutBoolean("DriveShifter", solenoidShifter.Get());

    SmartDashboard::PutNumber("GyroFused", GetGyroHeading());
}