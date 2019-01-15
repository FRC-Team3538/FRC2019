#pragma once

#include <subsystem/Drivebase.hpp>
#include <subsystem/Intake.hpp>
#include <subsystem/OtherManip.hpp>
#include <subsystem/DS.hpp>

class robotmap
{
  public:
    Drivebase drivebase;
    Intake intake;
    OtherManip manipB;
    DS ds;
    
};