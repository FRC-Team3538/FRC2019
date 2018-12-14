#pragma once

#include <VictorSP.h>
#include <SpeedControllerGroup.h>
#include <Solenoid.h>
#include <ctre/phoenix/MotorControl/CAN/WPI_VictorSPX.h>

using namespace ctre::phoenix::motorcontrol::can;

class Intake
{
  private:
    // Hardware setup
    VictorSP motorA1PWM {6};
    VictorSP motorA2PWM {7};

    WPI_VictorSPX motorA1 {6};
    WPI_VictorSPX motorA2 {7};
    SpeedControllerGroup motors{motorA1PWM, motorA2PWM, motorA1, motorA2};

    Solenoid solenoidArm{1};

  public:
    // Default Constructor
    Intake();

    // Actions
    void Deploy();
    void Retract();
    void SolenoidToggle();

    void Set(double speed);
    void Stop();

    bool SolenoidState();
};