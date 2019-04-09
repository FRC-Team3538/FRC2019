#pragma once

#include <frc/Solenoid.h>
#include <ctre/Phoenix.h>

using namespace frc;

class HatchManip
{
  private:
  
    // Hardware setup
    Solenoid deploy {5};
    Solenoid clamp {6};
    Solenoid floorIntake {7};

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

    WPI_VictorSPX hatchIntake {35};
};