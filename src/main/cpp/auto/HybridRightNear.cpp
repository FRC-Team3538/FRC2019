#include "auto/HybridRightNear.hpp"

#include <frc/smartdashboard/SmartDashboard.h>

// Name for Smart Dash Chooser
std::string HybridRightNear::GetName()
{
    return "5 - HybridRightNear";
}

// Initialization
// Constructor requires a reference to the robot map
HybridRightNear::HybridRightNear(robotmap &IO) : IO(IO)
{
    m_state = 0;
    m_autoTimer.Reset();
    m_autoTimer.Start();
    IO.drivebase.Stop();
    IO.drivebase.ResetGyro();
    IO.drivebase.GlobalReset();
}

//State Machine
void HybridRightNear::NextState()
{
    if(m_autoTimer.Get() > 0.2)
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
void HybridRightNear::Run()
{
    if (IO.ds.DriverPS.GetUpButton())
    {
        ToCargoShip();
    }
    else if (IO.ds.DriverPS.GetDownButton())
    {
        ToLoader();
    }

    UpdateSmartdash();
}

// SmartDash updater
void HybridRightNear::UpdateSmartdash()
{
    SmartDashboard::PutNumber("auto state", m_state);
}

void HybridRightNear::ResetState()
{
    m_state = 0;
}


void HybridRightNear::ToLoader()
{
    switch (m_state)
    {
        case 0:
        {
            IO.drivebase.ResetEncoders();
            IO.drivebase.ResetGyro();
            NextState();
            break;
        }
        case 1:
        {
            const double encdist = -44.0;
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
            const int gangle = 101;
            IO.drivebase.Turn(gangle);

            if ((std::abs(IO.drivebase.GetGyroHeading() - gangle) < ROT_TARGET) 
                && (std::abs(IO.drivebase.navx.GetRate()) < 2))
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
            const double encdist = 215.0;
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
            const int gangle = 90;
            IO.drivebase.Turn(gangle);

            break;
        }
    }

}

void HybridRightNear::ToCargoShip()
{
    
    switch (m_state)
    {
        case 0:
        {
            IO.drivebase.ResetEncoders();
            IO.drivebase.ResetGyro();
            NextState();
            break;
        }
        case 1:
        {
            const double encdist = -76.0;
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
            const int gangle = 15;
            IO.drivebase.Turn(gangle);

            if ((std::abs(IO.drivebase.GetGyroHeading() - gangle) < ROT_TARGET) 
                && (std::abs(IO.drivebase.navx.GetRate()) < 2))
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
            const double encdist = -200.0;
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

            break;
        }
    }

}