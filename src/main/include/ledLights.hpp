#pragma once

#include <frc/I2C.h>
#include <string>

using namespace frc;

class LedLights
{
  private:

    I2C* Wire = new I2C(I2C::Port::kMXP, 4);

  public:
    // Default Constructor
    LedLights();
}; 