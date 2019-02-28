#include "subsystem/FrontClimber.hpp"

#include <frc/smartdashboard/SmartDashboard.h>

// Configure Hardware Settings
FrontClimber::FrontClimber()
{
    motor1.SetInverted(true);
    motor1.ConfigNominalOutputForward(0);
    motor1.ConfigNominalOutputReverse(0);
    motor1.ConfigPeakOutputForward(1);
    motor1.ConfigPeakOutputReverse(-0.5);
}

// Solenoid
void FrontClimber::Deploy()
{
    SolenoidDeploy.Set(true);
}

bool FrontClimber::isDeployed()
{
    return SolenoidDeploy.Get();
}

void FrontClimber::Retract()
{
    SolenoidDeploy.Set(false);
}

// Motor
void FrontClimber::Stop()
{
    motor1.StopMotor();
}

//Positive Speed is climbing / forward
void FrontClimber::Set(double speed)
{
    motor1.Set(speed);
}

void FrontClimber::UpdateSmartdash()
{
    SmartDashboard::PutNumber("FrontClimber CMD", motor1.Get());
    // SmartDashboard::PutNumber("FrontClimber Sol", SolenoidDeploy.Get());
}