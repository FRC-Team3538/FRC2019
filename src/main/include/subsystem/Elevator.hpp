#pragma once

#include <frc/DigitalInput.h>
#include <frc/Solenoid.h>
#include <ctre/Phoenix.h>

using namespace frc;
using namespace ctre::phoenix::motorcontrol::can;

class Elevator
{
  private:
    // Hardware setup
    WPI_TalonSRX motor1 {6};
    WPI_VictorSPX motor2 {7};

    DigitalInput LimitSwitchLower {0};
		DigitalInput LimitSwitchUpper {1};

    Solenoid solenoidPTO{1};

    // Scale Factor (Inches) / (Pulses)
    const double kScaleFactor = (45.0 - 9.375) / (31196.0);

    // Soft Limits
    const double kMin = 5.0;
    const double kMax = 50.0;

  public:
    // Default Constructor
    Elevator();

    // Actions
    void Set(double speed);
    void Stop();

    bool GetSwitchUpper();
    bool GetSwitchLower();

    void ResetEnc();
    double GetDistance();
    void SetPosition(double pos);

    void UpdateSmartdash();
};