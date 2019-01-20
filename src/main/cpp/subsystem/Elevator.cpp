#include "subsystem/Elevator.hpp"

// Configure Hardware Settings
Elevator::Elevator()
{
    motor1.SetInverted(false);
    motor2.SetInverted(true);
    
}

void Elevator::Stop()
{
    //motors.StopMotor();
    motors.Set(0.0);
}

//Positive Speed is intaking
void Elevator::Set(double speed)
{
    motors.Set(speed);
}

void Elevator::UpdateSmartdash()
{
    SmartDashboard::PutNumber("Elevator CMD", motor1.Get());
}