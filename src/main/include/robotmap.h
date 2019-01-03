#pragma once

#include <subsystem/Drivebase.h>
#include <subsystem/Intake.h>
#include <subsystem/OtherManip.h>
#include <subsystem/DS.h>

class robotmap
{
  public:
    Drivebase drivebase;
    Intake intake;
    OtherManip manipB;
    DS ds;
    
};
