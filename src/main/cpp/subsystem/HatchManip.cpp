#include "subsystem/HatchManip.hpp"

#include <frc/smartdashboard/SmartDashboard.h>

// Configure Hardware Settings
HatchManip::HatchManip()
{
    // Default State
    clamp.Set(false);
    eject.Set(false);
}

void HatchManip::Eject()
{
    eject.Set(true);
}

void HatchManip::Retract()
{
    eject.Set(false);
}

void HatchManip::Clamp()
{
    eject.Set(true);
}

void HatchManip::Unclamp()
{
    eject.Set(false);
}


void HatchManip::UpdateSmartdash()
{
    SmartDashboard::PutNumber("Hatch Clamp", clamp.Get());
    SmartDashboard::PutNumber("Hatch Eject", eject.Get());
}