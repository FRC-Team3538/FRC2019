#pragma once

#include <frc/DigitalInput.h>
#include <ctre/Phoenix.h>
#include <iostream>

using namespace frc;
using namespace ctre::phoenix::motorcontrol::can;

class Wrist
{
  private:
    // Hardware setup
    WPI_TalonSRX motor1 {8};

    DigitalInput LimitSwitchLower {4};
		DigitalInput LimitSwitchUpper {5};

    // Soft Limits
    const double kMin = -180;
    const double kMax = 10;

    // Scale Factor (Degrees) / (Pulses)
    const double kScale = (90 / 5140.0);

     //3790 90

    double prevError = 0;
    bool sensorOverride = false;
    bool oneShot = false;
    
    double wristManualCommand = 0.0;
    double wristPosTarget = 0.0;

  public:
    // Default Constructor
    Wrist();

    void Stop();
    void SetSpeed(double speed);

    bool GetSwitchUpper();
    bool GetSwitchLower();

    void ActivateSensorOverride();
    void DeactivateSensorOverride();
    void ActivateLimitSwitchOverride();

    double GetAngle();
    void ResetEnc();
    void SetAngle(double angle);
    double GetTargetAngle();

    void UpdateSmartdash();
};