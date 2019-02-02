#pragma once

#include <frc/SpeedControllerGroup.h>
#include <frc/Solenoid.h>
#include <frc/DigitalInput.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>

using namespace frc;
using namespace ctre::phoenix::motorcontrol::can;

class CargoIntake
{
  private:
    // Hardware setup
    WPI_VictorSPX motor1 {8};
    WPI_VictorSPX motor2 {9};

    Solenoid deploy{4};
    DigitalInput sensor{3};

  public:
    // Default Constructor
    CargoIntake();

    // Actions
    void Deploy();
    void Retract();
    void SolenoidToggle();

    void Set(double speed);
    void Stop();

    bool SolenoidState();

    void UpdateSmartdash();
};