#include "subsystem/OtherManip.h"

// Configure Hardware Settings
OtherManip::OtherManip()
{
    motorB1PWM.SetInverted(false);
    motorB2PWM.SetInverted(false);
    motorB1.SetInverted(false);
    motorB2.SetInverted(false);
}

void OtherManip::Deploy()
{
    solenoidArmB.Set(true);
}

void OtherManip::Retract()
{
    solenoidArmB.Set(false);
}

void OtherManip::Stop()
{
    motorsB.StopMotor();
}

void OtherManip::Forward()
{
    motorsB.Set(kMotorSpeed);
}

void OtherManip::Backward()
{
    motorsB.Set(-kMotorSpeed);
}