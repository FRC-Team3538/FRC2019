#pragma once

#include <frc/Solenoid.h>
#include <ctre/Phoenix.h>
#include <AHRS.h>
#include <iostream>

using namespace ctre::phoenix::motorcontrol::can;
using namespace frc;

class Drivebase
{
private:
  // Hardware setup
  WPI_TalonSRX motorLeft1{0};
  WPI_VictorSPX motorLeft2{1};
  WPI_VictorSPX motorLeft3{2};

  WPI_TalonSRX motorRight1{3};
  WPI_VictorSPX motorRight2{4};
  WPI_VictorSPX motorRight3{5};

  Solenoid solenoidShifter{0};

  AHRS navx{SPI::Port::kMXP, 200};

  // Encoder Scale Factor (Inches)/(Pulse)
  const double kScaleFactor = (1.0)/(1.0);

public:
  // Default Constructor
  Drivebase();

  // Actions
  void Arcade(double forward, double rotate);
  void Stop();

  void SetHighGear();
  void SetLowGear();

  void ResetEncoders();
  double GetEncoderPositionLeft();
  double GetEncoderPositionRight();

  void ResetGyro();
  double GetGyroHeading();

  void UpdateSmartdash();
};