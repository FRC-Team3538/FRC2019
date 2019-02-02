#include "subsystem/CargoManip.hpp"

// Configure Hardware Settings
CargoManip::CargoManip()
{
    motor1.SetInverted(false);
    motor2.SetInverted(false);

    motor2.Follow(motor1);
}

void CargoManip::Stop()
{
    motor1.StopMotor();
}

//Positive Speed is intaking
void CargoManip::Set(double speed)
{
    motor1.Set(speed);
}

void CargoManip::UpdateSmartdash()
{
    SmartDashboard::PutNumber("Cargo Manip 1", motor1.Get());
}