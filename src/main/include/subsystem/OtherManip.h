#pragma once

#include <VictorSP.h>
#include <SpeedControllerGroup.h>
#include <Solenoid.h>
#include <ctre/phoenix/MotorControl/CAN/WPI_VictorSPX.h>

using namespace ctre::phoenix::motorcontrol::can;
class OtherManip
{
  private:
    // Hardware setup
    VictorSP motorB1PWM {8};
    VictorSP motorB2PWM {9};

    WPI_VictorSPX motorB1 {8};
    WPI_VictorSPX motorB2 {9};
    SpeedControllerGroup motorsB{motorB1PWM, motorB2PWM, motorB1, motorB2};

    Solenoid solenoidArmB{2};

    const double kMotorSpeed = 1;

  public:
    // Default Constructor
    OtherManip();

    // Actions
    void Deploy();
    void Retract();
    
    void Forward();
    void Backward();
    void Stop();
};

