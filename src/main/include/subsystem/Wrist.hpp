#pragma once

#include <frc/DigitalInput.h>
#include <ctre/Phoenix.h>

using namespace frc;
using namespace ctre::phoenix::motorcontrol::can;

class Wrist
{
  private:
    // Hardware setup
    WPI_TalonSRX motor1 {8};

    DigitalInput LimitSwitchLower {2};
		DigitalInput LimitSwitchUpper {3};

    // Soft Limits
    const double kMin = 5;
    const double kMax = -110;
    const double kScale = 4096.0;

    double targetAngle = 0;
    bool sensorOverride = false;

  public:
    // Default Constructor
    Wrist();

    void Stop();
    void Set(double speed);

    bool GetSwitchUpper();
    bool GetSwitchLower();

    void ActivateSensorOverride();
    void DeactivateSensorOverride();

    double GetAngle();
    void ResetAngle();
    void SetAngle(double angle);

    void UpdateSmartdash();
};