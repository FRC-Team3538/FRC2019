#pragma once

#include <frc/Solenoid.h>
#include <frc/DigitalInput.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>

using namespace frc;
using namespace ctre::phoenix::motorcontrol::can;

class CargoManip
{
  private:
    // Hardware setup
    WPI_VictorSPX motor1 {9};
    WPI_VictorSPX motor2 {10};

    DigitalInput LimitSwitch {4};

  public:
    // Default Constructor
    CargoManip();

    // Actions
    void Set(double speed);
    void Stop();

    void UpdateSmartdash();
};