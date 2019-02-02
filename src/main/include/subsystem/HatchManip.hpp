#pragma once

#include <frc/VictorSP.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/Solenoid.h>
//#include <ctre/phoenix/MotorControl/CAN/WPI_VictorSPX.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>

using namespace frc;
using namespace ctre::phoenix::motorcontrol::can;

class HatchManip
{
  private:
    // Hardware setup
    Solenoid clamp{2};
    Solenoid eject{3};

  public:
    // Default Constructor
    HatchManip();

    // Actions
    void Deploy();
    void Retract();
    void SolenoidToggle();

    bool SolenoidState();

    void UpdateSmartdash();
};