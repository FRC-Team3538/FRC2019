#include "subsystem/Intake.hpp"

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

bool Intake::SolenoidState(){
    return solenoidArm.Get();
}

void Intake::SolenoidToggle(){
    bool PCM2 = SolenoidState();
    solenoidArm.Set(!PCM2);
}
void Intake::UpdateSmartdash()
{
    SmartDashboard::PutNumber("auxMotorA", motors.Get());
    SmartDashboard::PutNumber("auxSolenoidA", solenoidArm.Get());
}