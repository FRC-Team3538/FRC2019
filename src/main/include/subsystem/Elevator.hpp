#pragma once

#include <frc/VictorSP.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/Solenoid.h>
//#include <ctre/phoenix/MotorControl/CAN/WPI_VictorSPX.h>
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

    SpeedControllerGroup motors{motor1, motor2}; 

  public:
    // Default Constructor
    Elevator();

    // Actions
    void Set(double speed);
    void Stop();

    void UpdateSmartdash();
};