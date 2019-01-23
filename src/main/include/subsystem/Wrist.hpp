#pragma once

#include <frc/VictorSP.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/Solenoid.h>
#include <frc/AnalogInput.h>
#include <frc/AnalogPotentiometer.h>
//#include <ctre/phoenix/MotorControl/CAN/WPI_VictorSPX.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>

using namespace frc;
using namespace ctre::phoenix::motorcontrol::can;

class Wrist
{
  private:
    // Hardware setup
    WPI_VictorSPX motor1 {8};
    AnalogInput analogInput {3};
	  AnalogPotentiometer pot {&analogInput, 270, -270 / 2};

  public:
    // Default Constructor
    Wrist();

    // Actions
    bool SetAngle(double angle);

    void Set(double speed);
    void Stop();

    void UpdateSmartdash();
};