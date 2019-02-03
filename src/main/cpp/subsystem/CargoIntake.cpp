#include "subsystem/CargoIntake.hpp"

#include <frc/smartdashboard/SmartDashboard.h>

// Configure Hardware Settings
CargoIntake::CargoIntake()
{
    motor1.SetInverted(false);
    motor2.SetInverted(false);

    motor2.Follow(motor1);
}

void CargoIntake::Deploy()
{
    //deployeploy.Set(true);
}

void CargoIntake::Retract()
{
    //deploy.Set(false);
}

void CargoIntake::Stop()
{
    motor1.StopMotor();
}

// Positive Speed is intaking
void CargoIntake::Set(double speed)
{
    motor1.Set(speed);
}

bool CargoIntake::SolenoidState(){
    return SolenoidDeploy.Get();
}

void CargoIntake::SolenoidToggle(){
    bool PCM2 = SolenoidState();
    SolenoidDeploy.Set(!PCM2);
}

void CargoIntake::UpdateSmartdash()
{
    SmartDashboard::PutNumber("Cargo Intake CMD", motor1.Get());
    SmartDashboard::PutNumber("Cargo Intake Sol", SolenoidDeploy.Get());
}