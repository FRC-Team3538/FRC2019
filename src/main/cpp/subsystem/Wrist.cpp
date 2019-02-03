#include "subsystem/Wrist.hpp"

#include <frc/smartdashboard/SmartDashboard.h>

// Configure Hardware Settings
Wrist::Wrist()
{
    motor1.SetInverted(false);

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
    double pos = GetAngle();

    if ((pos > kMax || GetSwitchUpper() ) && speed > 0.0) {
        motor1.Set(0.0);
    }
    else if ((pos < kMin || GetSwitchLower() ) && speed < 0.0) {
        motor1.Set(0.0);
    } 
    else
    {
        motor1.Set(speed);
    }
    
    
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
    // TODO
}

// Closed loop control
void Wrist::SetAngle(double angle)
{
    // TODO
}

double Wrist::GetAngle()
{
    // TODO
    return 0.0;
}

void Wrist::UpdateSmartdash()
{
    SmartDashboard::PutNumber("Wrist Motor", motor1.Get());
    SmartDashboard::PutNumber("Wrist Angle", GetAngle());
}