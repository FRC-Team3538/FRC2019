#pragma once

#include <frc/Solenoid.h>

using namespace frc;

class HatchManip
{
  private:
  
    // Hardware setup
    Solenoid deploy {5};
    Solenoid clamp {4};
    Solenoid floorIntake {6};

  public:
    // Default Constructor
    HatchManip();

    // Actions
    void Deploy();
    void Retract();

    void FloorIntakeDown();
    void FloorIntakeUp();

    void Clamp();
    void Unclamp();

    bool Deployed();

    void UpdateSmartdash();
};