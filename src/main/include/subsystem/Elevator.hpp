#pragma once

#include <frc/VictorSP.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/Solenoid.h>
#include <frc/DigitalInput.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>

using namespace frc;
using namespace ctre::phoenix::motorcontrol::can;

class Elevator
{
  private:
    // Hardware setup
    WPI_TalonSRX motor1 {6};
    WPI_VictorSPX motor2 {7};

    DigitalInput LimitSwitchLower {8};
		DigitalInput LimitSwitchUpper {9};

    SpeedControllerGroup motors{motor1, motor2}; 

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

    void UpdateSmartdash();
};