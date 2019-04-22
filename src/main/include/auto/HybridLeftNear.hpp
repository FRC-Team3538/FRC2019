#pragma once

#include <string>

#include <frc/Timer.h>

#include "AutoInterface.hpp"
#include <iostream>
#include "robotmap.hpp"

class HybridLeftNear : public AutoInterface
{
  public:
    // Name of this program, used by SmartDash
    static std::string GetName();

  private:
    // Get a referance to the robotmap
    robotmap &IO;

    // State Variables
    int m_state;
    Timer m_autoTimer;

    void NextState();

    double heading;
    bool timer = false;

    const double ROT_TARGET = 4.0;
    const double LIN_TARGET = 4.0;

  public:
    // Constructor requires a reference to the RobotMap
    HybridLeftNear() = delete;
    HybridLeftNear(robotmap &);

    // Auto Program Logic
    void Run(); 

    void ResetState();

    void UpdateSmartdash();

    void ToCargoShip();
    void ToLoader();
    void BackRocket();
    void LoaderToRocket();
};