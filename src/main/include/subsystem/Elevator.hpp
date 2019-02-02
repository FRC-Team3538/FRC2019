#pragma once

#include <frc/DigitalInput.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>

using namespace frc;
using namespace ctre::phoenix::motorcontrol::can;

class Elevator
{
  private:
    // Hardware setup
    WPI_TalonSRX motor1 {3};
    WPI_VictorSPX motor2 {12};

    DigitalInput LimitSwitchLower {1};
		DigitalInput LimitSwitchUpper {2};

  public:
    // Default Constructor
    Elevator();

    // Actions
    void Set(double speed);
    void Stop();
    void switchUpper();
    void switchLower();
    double GetDistance();
    void resetEnc();
    void setPosition(double pos);

    void UpdateSmartdash();
};