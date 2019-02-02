#include "subsystem/Drivebase.hpp"
#include <frc/smartDashboard/SmartDashboard.h>

Drivebase::Drivebase()
{
    // Link motors together

    // Invert one side of the drive
    motorLeft1.SetInverted(false);

    motorRight1.SetInverted(true);

    motorLeft2.Follow(motorLeft1);
    motorLeft3.Follow(motorLeft1);

    motorRight2.Follow(motorRight1);
    motorRight3.Follow(motorRight1);

    // set default shifter state
    solenoidShifter.Set(false);

    motorRight1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);
    motorRight1.ConfigVelocityMeasurementPeriod(VelocityMeasPeriod::Period_25Ms, 0);
    motorRight1.ConfigVelocityMeasurementWindow(32, 0);
    motorRight1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_3_Quadrature, 3, 100);

    motorLeft1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);
    motorLeft1.ConfigVelocityMeasurementPeriod(VelocityMeasPeriod::Period_25Ms, 0);
    motorLeft1.ConfigVelocityMeasurementWindow(32, 0);
    motorLeft1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_3_Quadrature, 3, 100);
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

void Drivebase::UpdateSmartdash()
{
    std::string moL = "DriveLeft";
    std::string moR = "DriveRight";

    SmartDashboard::PutNumber(moL, motorLeft1.Get());
    SmartDashboard::PutNumber(moR, motorRight1.Get());

    SmartDashboard::PutNumber("EncVelL", motorLeft1.GetSensorCollection().GetQuadratureVelocity());
    SmartDashboard::PutNumber("EncPosL", motorLeft1.GetSensorCollection().GetQuadraturePosition());
    SmartDashboard::PutNumber("EncVelR", motorRight1.GetSensorCollection().GetQuadratureVelocity());
    SmartDashboard::PutNumber("EncPosR", motorRight1.GetSensorCollection().GetQuadraturePosition());

    SmartDashboard::PutBoolean("High Gear", solenoidShifter.Get());
    SmartDashboard::PutNumber("GyroFused", navx.GetFusedHeading());
}