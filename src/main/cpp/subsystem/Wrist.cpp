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

    if (GetAngle() > 45.0 && speed > 0.0) {
        motor1.Set(0.0);
    }
    if (GetAngle() < (-45.0) && speed < 0.0) {
        motor1.Set(0.0);
    }
}

bool Wrist::SetAngle(double angle)
{
    //motor1.Set(angle);
    return false;
}

double Wrist::GetAngle()
{
    /*
    34 -90
    -55 0
    -133 90
    */
    return (pot.Get() + 50.0 )*(-1);
}

void Wrist::setPosition(double pos)
{
    
}

void Wrist::UpdateSmartdash()
{
    SmartDashboard::PutNumber("Wrist Pot", GetAngle());
    SmartDashboard::PutNumber("Wrist Analog Input Voltage", analogInput.GetVoltage());
    SmartDashboard::PutNumber("Wrist Motor", motor1.Get());
}