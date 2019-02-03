#pragma once

//#include <ctre/phoenix/MotorControl/CAN/WPI_TalonSRX.h>
//#include <ctre/phoenix/MotorControl/CAN/WPI_VictorSPX.h>
#include <frc/Solenoid.h>
#include <AHRS.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <ctre/Phoenix.h>
#include <frc/VictorSP.h>
#include <frc/SpeedControllerGroup.h>

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

  VictorSP motorLeft1PWM{0};
  VictorSP motorLeft2PWM{1};
  VictorSP motorLeft3PWM{2};

  VictorSP motorRight1PWM{3};
  VictorSP motorRight2PWM{4};
  VictorSP motorRight3PWM{5};

  SpeedControllerGroup DriveLeft{motorLeft1PWM, motorLeft2PWM, motorLeft3PWM, motorLeft1};
  SpeedControllerGroup DriveRight{motorRight1PWM, motorRight2PWM, motorRight3PWM, motorRight1};

  SpeedControllerGroup frontLeft{motorLeft1, motorLeft1PWM};
  SpeedControllerGroup frontRight{motorRight1, motorRight1PWM};
  SpeedControllerGroup backLeft{motorLeft2, motorLeft2PWM};
  SpeedControllerGroup backRight{motorRight2, motorRight2PWM};
  Solenoid solenoidShifter{0};

  AHRS navx{SPI::Port::kMXP, 200};


 
  

  enum Constants {
	/* Talon SRX/ Victor SPX will supported multiple (cascaded) PID loops.
	 * For now we just want the primary one.
	 */
	kPIDLoopIdx = 0,

	/*
	 * set to zero to skip waiting for confirmation, set to nonzero to wait
	 * and report to DS if action fails.
	 */
	kTimeoutMs = 30
  };

bool slave = false;

public:
  // Default Constructor
  Drivebase();

  void SlaveMotors();
  void FreeSlaves();
  
  // Actions
  void Tank(double left, double right);
  void Arcade(double forward, double rotate);
  void Holonomic(double forward, double rotate, double strafe);
  void Stop();

  void SetHighGear();
  void SetLowGear();

  void UpdateSmartdash();
  void Log();

  double EncPosL();
  double EncPosR();
  void ResetEnc();

  double GetGyroAngle();

  //void drivePosition(double pos);
};