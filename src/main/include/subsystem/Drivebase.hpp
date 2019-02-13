#pragma once

#include <frc/Solenoid.h>
#include <ctre/Phoenix.h>
#include <AHRS.h>
#include <iostream>

using namespace ctre::phoenix::motorcontrol::can;
using namespace ctre::phoenix::motorcontrol;
using namespace frc;

class Drivebase
{
private:
  // Hardware setup
  enum motors{L1 = 0, L2, L3, R1, R2, R3};

  WPI_TalonSRX motorLeft1{motors::L1};
  WPI_VictorSPX motorLeft2{motors::L2};
  WPI_VictorSPX motorLeft3{motors::L3};

  WPI_TalonSRX motorRight1{motors::R1};
  WPI_VictorSPX motorRight2{motors::R2};
  WPI_VictorSPX motorRight3{motors::R3};

  Solenoid solenoidShifter{0};

  AHRS navx{SPI::Port::kMXP, 200};

  // Encoder Scale Factor (Inches)/(Pulse)
  const double kScaleFactor = (1.0/4096.0) * 6 * 3.1415;

  enum kRemote{Remote0 = 0, Remote1};
  enum PIDind{primary = 0, aux};
  enum slots{Forward = 0, Turning, Slot2, Slot3};

  double prevError_rotation = 0;

  #define KP_ROTATION (0.007)
  #define KI_ROTATION (0.0001)
  #define KD_ROTATION (0.00075)

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

  void DriveForward(double distance);
  void Turn (double degrees);
};