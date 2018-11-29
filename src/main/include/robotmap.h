#pragma once

#include <ctre/phoenix/MotorControl/CAN/WPI_TalonSRX.h>
#include <SpeedControllerGroup.h>
#include <Drive/DifferentialDrive.h>

using namespace ctre::phoenix::motorcontrol::can;

class robotmap {

 public:
    // Drive base
    WPI_TalonSRX driveRight1{0};
    WPI_TalonSRX driveRight2{1};
    WPI_TalonSRX driveRight3{2};
    SpeedControllerGroup driveRight{driveRight1, driveRight2, driveRight3};
    
    WPI_TalonSRX driveLeft1{4};
    WPI_TalonSRX driveLeft2{5};
    WPI_TalonSRX driveLeft3{6};
    SpeedControllerGroup driveLeft{driveLeft1, driveLeft2, driveLeft3};

    DifferentialDrive driveBase{driveLeft, driveRight};

    robotmap();
};
