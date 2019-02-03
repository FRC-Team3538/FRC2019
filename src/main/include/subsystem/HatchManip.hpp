#pragma once

#include <frc/Solenoid.h>

using namespace frc;

class HatchManip
{
  private:
  
    // Hardware setup
    Solenoid clamp{2};
    Solenoid eject{3};

  public:
    // Default Constructor
    HatchManip();

    // Actions
    void Eject();
    void Retract();

    void Clamp();
    void Unclamp();

    void UpdateSmartdash();
};