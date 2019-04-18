#pragma once

#include <frc/Solenoid.h>
#include <ctre/Phoenix.h>

using namespace frc;
using namespace ctre::phoenix::motorcontrol::can;

class FrontClimber
{
  private:
    // Hardware setup
    // WPI_VictorSPX motor1 {31};
    // WPI_VictorSPX motor2 {30};

    // WPI_VictorSPX winch1 {32};
    // WPI_VictorSPX winch2 {33};

    //Solenoid SolenoidDeploy{5};

  public:
    // Default Constructor
    FrontClimber();

    // Actions
    void Deploy();
    void Retract();
    bool isDeployed();

    void Stop();
    void Set(double speed);
    void SetWinch(double speed);

    void UpdateSmartdash();
};