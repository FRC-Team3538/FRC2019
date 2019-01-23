#pragma once

#include <subsystem/DS.hpp>
#include <subsystem/Drivebase.hpp>
#include <subsystem/Elevator.hpp>
#include <subsystem/Claw.hpp>
#include <subsystem/Wrist.hpp>

class robotmap
{
  public:
    DS ds;
    Drivebase drivebase;
    Elevator elevator;
    Claw claw;
    Wrist wrist;
};