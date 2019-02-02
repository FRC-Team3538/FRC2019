#pragma once

#include <frc/Solenoid.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>
#include <AHRS.h>

using namespace ctre::phoenix::motorcontrol::can;
using namespace frc;

class Drivebase
{
private:
  // Hardware setup
  WPI_TalonSRX motorLeft1{0};
  WPI_VictorSPX motorLeft2{1};
  WPI_VictorSPX motorLeft3{2};

  WPI_TalonSRX motorRight1{15};
  WPI_VictorSPX motorRight2{14};
  WPI_VictorSPX motorRight3{13};

  Solenoid solenoidShifter{0};

  AHRS navx{SPI::Port::kMXP, 200};

public:
  // Default Constructor
  Drivebase();

  // Actions
  void Arcade(double forward, double rotate);
  void Stop();

  void SetHighGear();
  void SetLowGear();

  void UpdateSmartdash();
};