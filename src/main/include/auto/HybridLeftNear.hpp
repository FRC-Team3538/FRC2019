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

  public:
    // Constructor requires a reference to the RobotMap
    HybridLeftNear() = delete;
    HybridLeftNear(robotmap &);

    // Auto Program Logic
    void Run(); // 0 is to go to the near bay, 1 is to return

    void ResetState();

    void UpdateSmartdash();

    void ToCargoShip();
    void ToLoader();
};