#pragma once

#include <subsystem/DS.hpp>
#include <subsystem/Drivebase.hpp>
#include <subsystem/Elevator.hpp>
#include <subsystem/Wrist.hpp>
#include <subsystem/CargoManip.hpp>
#include <subsystem/HatchManip.hpp>
#include <subsystem/CargoIntake.hpp>
#include <subsystem/FrontClimber.hpp>
#include <subsystem/Vision.hpp>

class robotmap
{
  public:
    DS ds;
    Drivebase drivebase;
    Elevator elevator;
    Wrist wrist;
    CargoManip cargoManip;
    HatchManip hatchManip;
    CargoIntake cargoIntake;
    FrontClimber frontClimber;
    Vision vision;
};