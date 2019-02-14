#include "auto/AutoMachine.hpp"

#include <frc/smartdashboard/SmartDashboard.h>

// Name for Smart Dash Chooser
std::string AutoMachine::GetName()
{
    return "2 - AutoMachine";
}

// Initialization
// Constructor requires a reference to the robot map
AutoMachine::AutoMachine(robotmap &IO) : IO(IO)
{
    m_state = 0;
    m_autoTimer.Reset();
    m_autoTimer.Start();
    IO.drivebase.Stop();
}

//State Machine
void AutoMachine::NextState()
{
    m_state++;
    m_autoTimer.Reset();
    m_autoTimer.Start();
}

// Execute the program
void AutoMachine::Run()
{
    UpdateSmartdash();

    switch (m_state)
    {
    case 0:
    {
        int encdist = 55;
        IO.drivebase.DriveForward(encdist);
        if (std::abs(IO.drivebase.GetEncoderPositionLeft() - encdist) < 5 && std::abs(IO.drivebase.GetEncoderPositionRight() - encdist) < 5)
        {
            NextState();
        }
        break;
    }
    case 1:
    {
        int gangle = -50;
        IO.drivebase.Turn(gangle);
        if (std::abs(IO.drivebase.GetGyroHeading() - gangle) < 5)
        {
            IO.drivebase.ResetEncoders();
            NextState();
        }
        break;
    }
    case 2:
    {
        int encdist = 70;
        IO.drivebase.DriveForward(encdist);
        if (std::abs(IO.drivebase.GetEncoderPositionLeft() - encdist) < 5 && std::abs(IO.drivebase.GetEncoderPositionRight() - encdist) < 5)
        {
            NextState();
        }
        break;
    }
    case 3:
    {
        int gangle = -25;
        IO.drivebase.Turn(gangle);
        if (std::abs(IO.drivebase.GetGyroHeading() - gangle) < 5)
        {
            IO.drivebase.ResetEncoders();
            NextState();
        }
        break;
    }
    case 4:
    {
        //Auto Box Transform
        IO.vision.Run();
        double error = IO.vision.data.cmd;
        IO.vision.CVT = true;
        if (IO.vision.data.data)
        {
            if (IO.vision.data.distance >= 70)
            {
                IO.drivebase.Arcade(0, 0);
            }
            else
            {
                IO.drivebase.Arcade(-0.15, IO.vision.data.cmd);
            }
        }
        if ((std::abs(error) < 0.05) && (IO.vision.data.distance >= 70))
        {
            NextState();
        }
    }
    default:
        IO.drivebase.Stop();
        IO.vision.CVT = false;
    }
}

// SmartDash updater
void AutoMachine::UpdateSmartdash()
{
    SmartDashboard::PutNumber("auto state", m_state);
}