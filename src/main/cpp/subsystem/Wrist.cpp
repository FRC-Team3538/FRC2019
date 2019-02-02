#include "subsystem/Wrist.hpp"

// Configure Hardware Settings
Wrist::Wrist()
{
    motor1.SetInverted(false);
}

void Wrist::Stop()
{
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
    //return (pot.Get() + 50.0 )*(-1);
    return 0;
}

void Wrist::setPosition(double pos)
{
    //double error = (pos - GetAngle());
    //double kp = 0.05;

    //Set(error * kp);
}

void Wrist::UpdateSmartdash()
{
    SmartDashboard::PutNumber("Wrist Angle", GetAngle());
    SmartDashboard::PutNumber("Wrist Motor", motor1.Get());
}