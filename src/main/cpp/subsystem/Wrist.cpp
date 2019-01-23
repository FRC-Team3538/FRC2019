#include "subsystem/Wrist.hpp"

// Configure Hardware Settings
Wrist::Wrist()
{
    motor1.SetInverted(false);
    
}

void Wrist::Stop()
{
    //motors.StopMotor();
    motor1.Set(0.0);
}

//Positive Speed is intaking
void Wrist::Set(double speed)
{
    motor1.Set(speed);
}

bool Wrist::SetAngle(double angle)
{
    //motor1.Set(angle);
    return false;
}

void Wrist::UpdateSmartdash()
{
    SmartDashboard::PutNumber("Wrist Pot", pot.Get());
    SmartDashboard::PutNumber("Wrist Analog Input Voltage", analogInput.GetVoltage());
    SmartDashboard::PutNumber("Wrist Analog Input Value", analogInput.GetValue());
    SmartDashboard::PutNumber("Wrist Motor", motor1.Get());
}