#include "subsystem/HatchManip.hpp"

// Configure Hardware Settings
HatchManip::HatchManip()
{
    clamp.Set(false);
    eject.Set(false);
}

void HatchManip::Deploy()
{
    clamp.Set(true);
}

void HatchManip::Retract()
{
    eject.Set(false);
}

bool HatchManip::SolenoidState(){
    return clamp.Get();
}

void HatchManip::SolenoidToggle(){
    bool PCM2 = SolenoidState();
    clamp.Set(!PCM2);
}
void HatchManip::UpdateSmartdash()
{
    SmartDashboard::PutNumber("Hatch Clamp", clamp.Get());
    SmartDashboard::PutNumber("Hatch Eject", eject.Get());
}