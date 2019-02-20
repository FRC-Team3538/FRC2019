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

    DigitalInput LimitSwitchELower {0};
    DigitalInput LimitSwitchELower2 {1};
		DigitalInput LimitSwitchEUpper {2};
    DigitalInput LimitSwitchGanLeft {3};
    DigitalInput LimitSwitchGanRight {4};

    Solenoid solenoidPTO{1};

    // Scale Factor (Inches) / (Pulses)
    const double kScaleFactor = (45.0 - 9.375) / (31196.0);

    // Soft Limits
    const double kMin = 5.0;
    const double kMax = 50.0;

    double targetPos = 0;
    bool sensorOverride = false;

  public:
    // Default Constructor
    Elevator();

    // Actions
    void Set(double speed);
    void Stop();

    bool GetSwitchUpper();
    bool GetSwitchLower1();
    bool GetSwitchLower2();
    bool GetGanSwitchLeft();
    bool GetGanSwitchRight();

    void ActivateSensorOverride();
    void DeactivateSensorOverride();

    void ActivateGantry();
    void DeactivateGantry();

    void ResetEnc();
    double GetDistance();
    void SetPosition(double pos);

    void UpdateSmartdash();
};