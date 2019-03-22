#include "auto/HybridLeftNear.hpp"

#include <frc/smartdashboard/SmartDashboard.h>

// Name for Smart Dash Chooser
std::string HybridLeftNear::GetName()
{
    return "4 - HybridLeftNear";
}

// Initialization
// Constructor requires a reference to the robot map
HybridLeftNear::HybridLeftNear(robotmap &IO) : IO(IO)
{
    m_state = 0;
    m_autoTimer.Reset();
    m_autoTimer.Start();
    IO.drivebase.Stop();
    IO.drivebase.ResetGyro();
    IO.drivebase.GlobalReset();
}

//State Machine
void HybridLeftNear::NextState()
{
    m_state++;
    m_autoTimer.Reset();
    m_autoTimer.Start();
    IO.drivebase.ResetEncoders();
    IO.drivebase.GlobalReset();
    timer = false;
}

// Execute the program
void HybridLeftNear::Run()
{
    UpdateSmartdash();
    if (IO.ds.DriverPS.GetRightButton())
    {
        ToCargoShip();
    }
    else if (IO.ds.DriverPS.GetDownButton())
    {
        ToLoader();
    }
    else
    {
        m_state = 0;
    }
}

// SmartDash updater
void HybridLeftNear::UpdateSmartdash()
{
    SmartDashboard::PutNumber("auto state", m_state);
}

void HybridLeftNear::ResetState()
{
    m_state = 0;
}

void HybridLeftNear::ToCargoShip()
{
    switch (m_state)
    {
    case 0:
    {
        IO.drivebase.forwardHeading = 0;
        IO.drivebase.ResetEncoders();
        NextState();
        break;
    }
    case 1:
    {
        const double encdist = 100.0;
        IO.drivebase.DriveForward(encdist, 0.95);

        if ((std::abs(IO.drivebase.GetEncoderPosition() - encdist) < 3) && !timer)
        {
            m_autoTimer.Reset();
            m_autoTimer.Start();
            timer = true;
        }
        if ((m_autoTimer.Get() > 0.5) && (std::abs(IO.drivebase.GetEncoderPosition() - encdist) < 3))
        {
            NextState();
        }
        std::cout << IO.drivebase.GetEncoderPositionLeft() << std::endl;
        break;
    }
    case 2:
    {
        const int gangle = -90;
        IO.drivebase.Turn(gangle);
        if (std::abs(IO.drivebase.GetGyroHeading() - gangle) < 2)
        {
            IO.drivebase.ResetEncoders();
            NextState();
        }
        break;
    }

    default:
    {
    }
    }
}

void HybridLeftNear::ToLoader()
{
    switch (m_state)
    {
    case 0:
    {
        IO.drivebase.forwardHeading = 0;
        IO.drivebase.ResetEncoders();
        NextState();
        break;
    }
    case 1:
    {
        const double encdist = -30.0;
        IO.drivebase.DriveForward(encdist, 0.95);

        double encoderPosition = IO.drivebase.GetEncoderPosition();
        if ((std::abs(encoderPosition - encdist) < 3))
        {
            NextState();
        }

        std::cout << IO.drivebase.GetEncoderPositionLeft() << std::endl;
        break;
    }
    case 2:
    {
        const int gangle = -104;
        IO.drivebase.Turn(gangle);
        if ((std::abs(IO.drivebase.GetGyroHeading() - gangle) < 2) && (std::abs(IO.drivebase.navx.GetRate()) < 2))
        {
            IO.drivebase.ResetEncoders();
            NextState();
        }
        break;
    }
    case 3:
    {
        const double encdist = 225.0;
        IO.drivebase.DriveForward(encdist, 0.95);

        if ((std::abs(IO.drivebase.GetEncoderPosition() - encdist) < 3))
        {
            NextState();
        }
        std::cout << IO.drivebase.GetEncoderPositionLeft() << std::endl;
        break;
    }
    case 4:
    {
        const int gangle = -90;
        IO.drivebase.Turn(gangle);
        if (std::abs(IO.drivebase.GetGyroHeading() - gangle) < 5)
        {
            IO.drivebase.ResetEncoders();
        }
        break;
    }

    default:
    {
    }
    }
}