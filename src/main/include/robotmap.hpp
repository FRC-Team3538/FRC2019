#pragma once

#include <subsystem/DS.hpp>
#include <subsystem/Drivebase.hpp>
#include <subsystem/Elevator.hpp>
#include <subsystem/Wrist.hpp>
#include <subsystem/CargoManip.hpp>
#include <subsystem/CargoIntake.hpp>
#include <subsystem/HatchManip.hpp>

class robotmap
{
  public:
    DS ds;
    Drivebase drivebase;
    Elevator elevator;
    Wrist wrist;
    CargoManip cargoManip;
    CargoIntake cargoIntake;
    HatchManip hatchManip;
};