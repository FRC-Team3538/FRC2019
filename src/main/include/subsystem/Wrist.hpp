#pragma once

#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>

using namespace frc;
using namespace ctre::phoenix::motorcontrol::can;

class Wrist
{
  private:
    // Hardware setup
    WPI_TalonSRX motor1 {4};

  public:
    // Default Constructor
    Wrist();
    // Actions
    bool SetAngle(double angle);
    double GetAngle();
    void Set(double speed);
    void Stop();
    void setPosition(double pos);

    void UpdateSmartdash();
};