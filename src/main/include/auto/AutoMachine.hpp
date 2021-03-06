#pragma once

#include <string>

#include <frc/Timer.h>

#include "AutoInterface.hpp"
#include "robotmap.hpp"

class AutoMachine: public AutoInterface {
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

 public:
    // Constructor requires a reference to the RobotMap
    AutoMachine() = delete;
    AutoMachine(robotmap& );

    // Auto Program Logic
    void Run();

    void UpdateSmartdash();
    
};