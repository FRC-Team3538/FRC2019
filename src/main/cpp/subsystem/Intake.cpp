#include "subsystem/Intake.h"

// Configure Hardware Settings
Intake::Intake()
{
    motor1.SetInverted(false);
    motor2.SetInverted(false);

    solenoidArm.Set(false);
}

void Intake::Deploy()
{
    solenoidArm.Set(true);
}

void Intake::Retract()
{
    solenoidArm.Set(false);
}

void Intake::Stop()
{
    motors.StopMotor();
}

void Intake::Suck()
{
    motors.Set(kMotorSpeed);
}

void Intake::Spit()
{
    motors.Set(-kMotorSpeed);
}