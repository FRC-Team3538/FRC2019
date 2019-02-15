
#include <frc/smartdashboard/SmartDashboard.h>
#include "auto/AutoMachine.hpp"

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
        IO.drivebase.DriveForward(encdist, 0.45);
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
        int encdist = 65;
        IO.drivebase.DriveForward(encdist, 1);
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
        int encdist = 36;
        IO.drivebase.DriveForward(encdist, 1);
        if (std::abs(IO.drivebase.GetEncoderPositionLeft() - encdist) < 5 && std::abs(IO.drivebase.GetEncoderPositionRight() - encdist) < 5)
        {
            NextState();
        }
        break;
    }
    case 5:
    {
        //Auto Box Transform
        IO.vision.CVMode(true);
        Vision::returnData visionData = IO.vision.Run();
        double error = visionData.cmd;
        if (visionData.data && error != -3.14)
        {
            IO.drivebase.Arcade(0.15, -error);
        }
        if ((std::abs(error) < 0.05) && (visionData.distance >= 70))
        {
            NextState();
        }
        break;
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