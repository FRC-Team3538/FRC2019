#pragma once

#include <frc/VictorSP.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/Solenoid.h>
//#include <ctre/phoenix/MotorControl/CAN/WPI_VictorSPX.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>

using namespace frc;
using namespace ctre::phoenix::motorcontrol::can;

class CargoManip
{
  private:
    // Hardware setup
    WPI_VictorSPX motor1 {5};
    WPI_VictorSPX motor2 {6};

  public:
    // Default Constructor
    CargoManip();

    // Actions
    void Set(double speed);
    void Stop();

    void UpdateSmartdash();
};