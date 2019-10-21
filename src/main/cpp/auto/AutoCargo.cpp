#include "auto/AutoCargo.hpp"

#include <frc/smartdashboard/SmartDashboard.h>

// Name for Smart Dash Chooser
std::string AutoCargo::GetName()
{
    return "3 - AutoCargo";
}

// Initialization
// Constructor requires a reference to the robot map
AutoCargo::AutoCargo(robotmap &IO) : IO(IO)
{
    m_state = 0;
    m_autoTimer.Reset();
    m_autoTimer.Start();
    IO.drivebase.Stop();
    IO.drivebase.ResetGyro();
    IO.drivebase.GlobalReset();
}

//State Machine
void AutoCargo::NextState()
{
    m_state++;
    m_autoTimer.Reset();
    m_autoTimer.Start();
    IO.drivebase.ResetEncoders();
    IO.drivebase.GlobalReset();
}

// Execute the program
void AutoCargo::Run()
{
    UpdateSmartdash();
    switch (m_state)
    {
    case 0:
    {
        IO.drivebase.ResetEncoders();
        NextState();
        break;
    }
    case 1:
    {
        const double encdist = 144.0;
        IO.drivebase.DriveForward(encdist, 0.95);
        if (abs(((IO.drivebase.GetEncoderPositionRight() + IO.drivebase.GetEncoderPositionLeft()) / 2) - encdist) < 2)
        {
            //NextState();
        }
        break;
    }
    default:
        IO.drivebase.Stop();
    }
}

// SmartDash updater
void AutoCargo::UpdateSmartdash()
{
    SmartDashboard::PutNumber("auto state", m_state);
}