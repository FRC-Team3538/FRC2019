#pragma once

#include <string>

#include <frc/Timer.h>

#include "AutoInterface.hpp"
#include "robotmap.hpp"

#include <frc/smartdashboard/SmartDashboard.h>

class MotionMagiskTest: public AutoInterface {
 public:
    // Name of this program, used by SmartDash
    static std::string GetName();

 private:
    // Get a referance to the robotmap
    robotmap& IO;

    // State Variables
    int m_state;   
    Timer m_autoTimer;

    void NextState();

    bool oneShot = false;

 public:
    // Constructor requires a reference to the RobotMap
    MotionMagiskTest() = delete;
    MotionMagiskTest(robotmap& );

    // Auto Program Logic
    void Run();
    
};