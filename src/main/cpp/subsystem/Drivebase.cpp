#include "subsystem/Drivebase.h"
#include <SmartDashboard/SmartDashboard.h>

Drivebase::Drivebase()
{
    // Link motors together

    // Invert one side of the drive
    DriveLeft.SetInverted(false);

    DriveRight.SetInverted(true);

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

// Tanks Drive
void Drivebase::Tank(double left, double right)
{
    DriveLeft.Set(left);
    DriveRight.Set(right);
}

// Arcade Drive
void Drivebase::Arcade(double forward, double turn)
{
    DriveLeft.Set(forward - turn);
    DriveRight.Set(forward + turn);
}

// Stop!
void Drivebase::Stop()
{
    DriveLeft.StopMotor();
    DriveRight.StopMotor();
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

void Drivebase::Holonomic(double forward, double rotate, double strafe)
{
    double front_Left = forward - rotate + strafe;
    double front_Right = -(forward + rotate + strafe);
    double back_Left = forward - rotate - strafe;
    double back_Right = -(forward + rotate - strafe);

    double Magnitude = abs(forward) + abs(rotate) + abs(strafe);

    if (abs(front_Right) > Magnitude)
    {
        Magnitude = abs(front_Right);
    }
    if (abs(back_Left) > Magnitude)
    {
        Magnitude = abs(back_Left);
    }
    if (abs(back_Right) > Magnitude)
    {
        Magnitude = abs(back_Right);
    }

    if (Magnitude > 1)
    {
        front_Left /= Magnitude;
        front_Right /= Magnitude;
        back_Left /= Magnitude;
        back_Right /= Magnitude;
    }
    frontLeft.Set(front_Left);
    frontRight.Set(front_Right);
    backLeft.Set(back_Left);
    backRight.Set(back_Right);
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

    SmartDashboard::PutNumber("SolShifter", solenoidShifter.Get());
    SmartDashboard::PutNumber("GyroFused", navx.GetFusedHeading());
}