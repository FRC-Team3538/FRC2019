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

    DigitalInput LimitElvSwitchLower {0};
		DigitalInput LimitElvSwitchUpper {1};
    DigitalInput LimitSwitchGanLeft {2};
    DigitalInput LimitSwitchGanRight {3};

    Solenoid solenoidPTO{1};

    // Scale Factor (Inches) / (Pulses)
    const double kScaleFactor = (54.0 - 7.0) / (17344.0);
    /*
        Inches     Pulses
          7              0
          54        17,344

    */

    // Soft Limits
    const double kMin = 5.0;
    const double kMax = 50.0;

    double targetPos = 0;
    bool sensorOverride = false;
    bool oneShot = false;

  public:
    // Default Constructor
    Elevator();

    // Actions
    void Set(double speed);
    void Stop();

    bool GetElvSwitchUpper();
    bool GetElvSwitchLower();
    bool GetGanSwitchLeft();
    bool GetGanSwitchRight();

    void ActivateSensorOverride();
    void DeactivateSensorOverride();

    void ActivateGantry();
    void DeactivateGantry();
    void ToggleGantry();

    void ResetEnc();
    double GetDistance();
    void SetPosition(double pos);

    void UpdateSmartdash();
};