#pragma once

#include <frc/VictorSP.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/Solenoid.h>
#include <frc/DoubleSolenoid.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>
//#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h>
//#include <ctre/phoenix/motorcontrol/can/WPI_VictorSPX.h>

using namespace frc;
using namespace ctre::phoenix::motorcontrol::can;

class Claw
{
  private:
    // Hardware setup
    WPI_VictorSPX motor1 {9};
    WPI_VictorSPX motor2 {10};
    DoubleSolenoid clamp {1, 2};

    SpeedControllerGroup motors{motor1, motor2}; 

  public:
    // Default Constructor
    Claw();

    // Actions
    void Open();
    void Close();
    void Compliant();
    void Set(double speed);
    void Stop();

    void UpdateSmartdash();
};