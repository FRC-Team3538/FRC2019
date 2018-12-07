#pragma once

#include <ctre/phoenix/MotorControl/CAN/WPI_TalonSRX.h>
#include <ctre/phoenix/MotorControl/CAN/WPI_VictorSPX.h>
#include <Solenoid.h>
#include <AHRS.h>

using namespace ctre::phoenix::motorcontrol::can;


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
    SpeedControllerGroup DriveLeft{motorLeft1PWM, motorLeft2PWM, motorLeft3PWM, motorLeft1, motorLeft2, motorLeft3};

    VictorSP motorRight1PWM{3};
    VictorSP motorRight2PWM{4};
    VictorSP motorRight3PWM{5};
    SpeedControllerGroup DriveRight{motorRight1PWM, motorRight2PWM, motorRight3PWM, motorRight1, motorRight2, motorRight3};

    Solenoid solenoidShifter{0}; 

    AHRS navx{ SPI::Port::kMXP, 200 };

  public:
    // Default Constructor
    Drivebase();

    // Actions
    void Tank(double left, double right);
    void Arcade(double forward, double rotate);
    void Stop();

    void SetHighGear();
    void SetLowGear();
};
