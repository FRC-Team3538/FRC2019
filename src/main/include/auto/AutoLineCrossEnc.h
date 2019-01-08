#pragma once

#include <string>

#include <Timer.h>

#include "AutoInterface.h"
#include "robotmap.h"

class AutoLineCrossEnc : public AutoInterface {
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

    bool forward(double distance, double speed);

 public:
    // Constructor requires a reference to the RobotMap
    AutoLineCrossEnc() = delete;
    AutoLineCrossEnc(robotmap& );

    // Auto Program Logic
    void Run();
    
};
