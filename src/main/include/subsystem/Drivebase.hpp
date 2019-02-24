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
  double prevError_forward = 0;
  double sumError_forward = 0;
  double prevError_rot = 0;
  double sumError_rotation = 0;

  bool oneShotAngle = false;

  #define KP_ROTATION (0.012) //0.012   0.05
  #define KI_ROTATION (0.0000) //0.0001
  #define KD_ROTATION (0.0001) //0.0001  0.0005

  #define KP_FORWARD (0.012)
  #define KI_FORWARD (0.0)
  #define KD_FORWARD (0.0)


public:
  // Default Constructor
  Drivebase();

  bool sensorOverride = false;
  double forwardHeading;
  // Actions
  void Arcade(double forward, double rotate);
  void Stop();
  void SetHighGear();
  void SetLowGear();
  
  void ActivateSensorOverride();
  void DeactivateSensorOverride();

  void ResetEncoders();
  double GetEncoderPositionLeft();
  double GetEncoderPositionRight();

  void ResetGyro();
  double GetGyroHeading();
  void GlobalReset();

  void UpdateSmartdash();

  void DriveForward(double distance, double currentLimit = 1.0);
  void Turn (double degrees);

  PigeonIMU * Hoothoot = new PigeonIMU(0);
};