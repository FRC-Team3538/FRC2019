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
    IO.drivebase.GlobalReset();
}

//State Machine
void HybridLeftNear::NextState()
{
    if (m_autoTimer.Get() > 0.15)
    {
        m_state++;
        m_autoTimer.Reset();
        m_autoTimer.Start();
        IO.drivebase.ResetEncoders();
        IO.drivebase.GlobalReset();
        timer = false;
    }
}

// Execute the program
void HybridLeftNear::Run()
{

    if (IO.ds.DriverPS.GetUpButton())
    {
        ToCargoShip();
    }
    else if (IO.ds.DriverPS.GetDownButton())
    {
        ToLoader();
    }
    else if (IO.ds.DriverPS.GetRightButton())
    {
        BackRocket();
    }

    UpdateSmartdash();
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

void HybridLeftNear::ToLoader()
{
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
        const double encdist = -38.0;
        IO.drivebase.forwardHeading = -90.0;
        IO.drivebase.DriveForward(encdist, 0.95);

        if ((std::abs(IO.drivebase.GetEncoderPosition() - encdist) < LIN_TARGET))
        {
            NextState();
        }
        else
        {
            m_autoTimer.Reset();
        }

        break;
    }
    case 2:
    {
        const int gangle = 165;
        IO.drivebase.Turn(gangle);

        if ((std::abs(IO.drivebase.GetGyroHeading() - gangle) < ROT_TARGET) && (std::abs(IO.drivebase.navx.GetRate()) < 2))
        {
            IO.drivebase.ResetEncoders();
            NextState();
        }
        else
        {
            m_autoTimer.Reset();
        }

        break;
    }
    case 3:
    {
        const double encdist = 200.0;
        IO.drivebase.DriveForward(encdist, 0.95);

        if ((std::abs(IO.drivebase.GetEncoderPosition() - encdist) < LIN_TARGET))
        {
            NextState();
        }
        else
        {
            m_autoTimer.Reset();
        }
        break;
    }
    case 4:
    {
        const int gangle = -180;
        IO.drivebase.Turn(gangle);

        IO.hatchManip.Deploy();
        IO.elevator.SetPosition(13);
        break;
    }
    }
}

void HybridLeftNear::ToCargoShip()
{

    switch (m_state)
    {
    case 0:
    {
        IO.drivebase.ResetEncoders();
        IO.drivebase.forwardHeading = 175;
        NextState();
        break;
    }
    case 1:
    {
        const double encdist = -48.0;
        IO.drivebase.DriveForward(encdist, 0.95);

        if ((std::abs(IO.drivebase.GetEncoderPosition() - encdist) < LIN_TARGET))
        {
            NextState();
        }
        else
        {
            m_autoTimer.Reset();
        }

        break;
    }
    case 2:
    {
        const int gangle = -16;
        IO.drivebase.Turn(gangle);

        if ((std::abs(IO.drivebase.GetGyroHeading() - gangle) < ROT_TARGET) && (std::abs(IO.drivebase.navx.GetRate()) < 2))
        {
            IO.drivebase.ResetEncoders();
            NextState();
        }
        else
        {
            m_autoTimer.Reset();
        }
        break;
    }
    case 3:
    {
        const double encdist = 210.0;
        IO.drivebase.DriveForward(encdist, 0.95);

        if ((std::abs(IO.drivebase.GetEncoderPosition() - encdist) < LIN_TARGET))
        {
            NextState();
        }
        else
        {
            m_autoTimer.Reset();
        }
        break;
    }
    case 4:
    {
        const int gangle = -90;
        IO.drivebase.Turn(gangle);

        IO.elevator.SetPosition(13);

        break;
    }
    }
}

void HybridLeftNear::BackRocket()
{
    switch (m_state)
    {
    case 0:
    {
        IO.drivebase.ResetEncoders();
        IO.drivebase.forwardHeading = 0;
        NextState();
        break;
    }
    case 1:
    {
        IO.elevator.SetPosition(12);
        if(IO.elevator.GetDistance() > 10){
            IO.hatchManip.Deploy();
        }

        const double encdist = -270.0;
        IO.drivebase.DriveForward(encdist, 1);
        IO.hatchManip.hatchIntake.Set(0.2);

        if (IO.drivebase.GetEncoderPosition() < -155.0)
        {
            IO.drivebase.forwardHeading = 40;
        }
        else if (IO.drivebase.GetEncoderPosition() < -77.5)
        {
            IO.drivebase.forwardHeading = 15;
        }

        if ((std::abs(IO.drivebase.GetEncoderPosition() - encdist) < LIN_TARGET))
        {
            NextState();
        }
        else
        {
            m_autoTimer.Reset();
        }

        break;
    }
    case 2:
    {
        IO.hatchManip.hatchIntake.Set(0.2);
        const int gangle = -30;
        IO.drivebase.Turn(gangle);
        if ((std::abs(IO.drivebase.GetGyroHeading() - gangle) < 6) && (std::abs(IO.drivebase.navx.GetRate()) < 2))
        {
            IO.drivebase.ResetEncoders();
            NextState();
        }
        break;
    }
    case 3:
    {
        IO.elevator.SetPosition(12);
        if (IO.elevator.GetDistance() > 10)
        {
            IO.hatchManip.Deploy();
        }
        break;
    }
    }
}