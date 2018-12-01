#pragma once

#include <VictorSP.h>
#include <SpeedControllerGroup.h>
#include <Solenoid.h>

class Intake
{
  private:
    // Hardware setup
    VictorSP motor1{10};
    VictorSP motor2{11};
    SpeedControllerGroup motors{motor1, motor2};

    Solenoid solenoidArm{1};

    const double kMotorSpeed = 0.8;

  public:
    // Default Constructor
    Intake();

    // Actions
    void Deploy();
    void Retract();

    void Suck();
    void Spit();
    void Stop();
};