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
    const double kMax = -135;

    // Scale Factor (Degrees) / (Pulses)
    const double kScale = (73.0 / 3116.0);

     //3790 90

    double prevError = 0;
    bool sensorOverride = false;
    bool oneShot = false;

  public:
    double wristPosTarget;
    // Default Constructor
    Wrist();

    void Stop();
    void SetSpeed(double speed);

    bool GetSwitchUpper();
    bool GetSwitchLower();

    void ActivateSensorOverride();
    void DeactivateSensorOverride();

    double GetAngle();
    void ResetEnc();
    void SetAngle(double angle);

    void UpdateSmartdash();
};