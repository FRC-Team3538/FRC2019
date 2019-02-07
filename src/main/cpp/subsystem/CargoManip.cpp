#include "subsystem/CargoManip.hpp"

#include <frc/smartdashboard/SmartDashboard.h>

// Configure Hardware Settings
CargoManip::CargoManip()
{
    motor1.SetInverted(false);
    motor2.SetInverted(true);

    motor2.Follow(motor1);
}

void CargoManip::Stop()
{
    motor1.StopMotor();
    motor2.StopMotor();
}

// Positive Speed is intaking
void CargoManip::Set(double speed)
{
    motor1.Set(speed);
    motor2.Set(speed);
}

void CargoManip::UpdateSmartdash()
{
    SmartDashboard::PutNumber("Cargo Manip CMD", motor1.Get());
}