#include "subsystem/Intake.h"

// Configure Hardware Settings
Intake::Intake()
{
    motorA1PWM.SetInverted(false);
    motorA2PWM.SetInverted(false);
    motorA1.SetInverted(false);
    motorA2.SetInverted(false);

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

//Positive Speed is intaking
void Intake::Set(double speed)
{
    motors.Set(speed);
}



