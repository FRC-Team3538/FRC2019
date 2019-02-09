#include "subsystem/Wrist.hpp"

#include <frc/smartdashboard/SmartDashboard.h>

// Configure Hardware Settings
Wrist::Wrist()
{
    motor1.SetInverted(false);
    motor1.ConfigPeakCurrentLimit(5);
    motor1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder);
    motor1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_3_Quadrature, 18);
    // TODO: Setup angle sensor
}

// Stop all motors
void Wrist::Stop()
{
    motor1.Set(0.0);
}

// Positive speed is up
void Wrist::Set(double speed)
{
    /*double pos = GetAngle();

    if ((pos > kMax || GetSwitchUpper() ) && speed > 0.0) {
        motor1.Set(0.0);
    }
    else if ((pos < kMin || GetSwitchLower() ) && speed < 0.0) {
        motor1.Set(0.0);
    } 
    else
    {
        motor1.Set(speed);
    }*/
    motor1.Set(speed);
    
}

// Limit Switches
bool Wrist::GetSwitchUpper()
{
    return LimitSwitchUpper.Get();
}

bool Wrist::GetSwitchLower()
{
    return LimitSwitchUpper.Get();
}

void Wrist::ResetAngle()
{
    motor1.SetSelectedSensorPosition(0);
}

// Closed loop control
void Wrist::SetAngle(double angle)
{
    //TODO
    targetAngle = angle;
}

double Wrist::GetAngle()
{
    return motor1.GetSensorCollection().GetQuadraturePosition();
    // double rots = motor1.GetSensorCollection().GetQuadraturePosition() / kScale;
    // double deg = rots * 360.0;
    // return deg;
}

void Wrist::ActivateSensorOverride()
{
    sensorOverride = true;
}

void Wrist::DeactivateSensorOverride()
{
    sensorOverride = false;
}

void Wrist::UpdateSmartdash()
{
    SmartDashboard::PutNumber("Wrist Motor", motor1.Get());
    SmartDashboard::PutNumber("Wrist Angle", GetAngle());
    SmartDashboard::PutNumber("Wrist Angle Target", targetAngle);
    SmartDashboard::PutBoolean("Wrist Sensor Override", sensorOverride);
}