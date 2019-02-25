#include "subsystem/HatchManip.hpp"

#include <frc/smartdashboard/SmartDashboard.h>

// Configure Hardware Settings
HatchManip::HatchManip()
{
    // Default State
    clamp.Set(false);
    deploy.Set(false);
    floorIntake.Set(false);
}

void HatchManip::Deploy()
{
    deploy.Set(true);
}

void HatchManip::Retract()
{
    deploy.Set(false);
}

bool HatchManip::Deployed()
{
    return deploy.Get();
}

void HatchManip::FloorIntakeDown()
{
    floorIntake.Set(true);
}
void HatchManip::FloorIntakeUp()
{
    floorIntake.Set(false);
}

void HatchManip::Clamp()
{
    clamp.Set(true);
}

void HatchManip::Unclamp()
{
    clamp.Set(false);
}


void HatchManip::UpdateSmartdash()
{
    SmartDashboard::PutBoolean("Hatch Clamp", clamp.Get());
    SmartDashboard::PutBoolean("Hatch Deploy", deploy.Get());
    SmartDashboard::PutBoolean("Hatch Floor", floorIntake.Get());
}