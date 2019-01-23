#include "subsystem/Claw.hpp"

// Configure Hardware Settings
Claw::Claw()
{
    motor1.SetInverted(false);
    motor2.SetInverted(false);
    
}

void Claw::Stop()
{
    //motors.StopMotor();
    motors.Set(0.0);
}

//Positive Speed is intaking
void Claw::Set(double speed)
{
    motors.Set(speed);
}

void Claw::Open()
{
    clamp.Set(DoubleSolenoid::Value::kReverse);
}

void Claw::Close()
{
    clamp.Set(DoubleSolenoid::Value::kForward);
}

void Claw::Compliant()
{
    clamp.Set(DoubleSolenoid::Value::kOff);
}

void Claw::UpdateSmartdash()
{
    SmartDashboard::PutNumber("Claw Motors", motors.Get());
    SmartDashboard::PutNumber("Claw Solenoid", clamp.Get());
}