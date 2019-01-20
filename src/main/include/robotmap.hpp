#pragma once

#include <subsystem/DS.hpp>
#include <subsystem/Drivebase.hpp>
#include <subsystem/Elevator.hpp>

class robotmap
{
  public:
    DS ds;
    Drivebase drivebase;
    Elevator elevator;
};