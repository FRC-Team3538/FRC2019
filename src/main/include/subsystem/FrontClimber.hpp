#pragma once

#include <frc/SpeedControllerGroup.h>
#include <frc/Solenoid.h>
#include <frc/DigitalInput.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>

using namespace frc;
using namespace ctre::phoenix::motorcontrol::can;

class FrontClimber
{
  private:
    // Hardware setup
    WPI_VictorSPX motor1 {13};

    Solenoid SolenoidDeploy{5};

  public:
    // Default Constructor
    FrontClimber();

    // Actions
    void Deploy();
    void Retract();

    void Set(double speed);
    void Stop();

    bool SolenoidState();

    void UpdateSmartdash();
};