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
        const double encdist = 195.0;
        IO.drivebase.DriveForward(encdist, 0.95);
        if ((IO.drivebase.GetEncoderPositionRight() + IO.drivebase.GetEncoderPositionLeft()) / 2 >= 30)
        {
            IO.drivebase.forwardHeading = 30;
        }
        if ((std::abs(IO.drivebase.GetEncoderPositionLeft() - encdist + 6) < 3) && (std::abs(IO.drivebase.GetEncoderPositionRight() - encdist - 6) < 3))
        {
            NextState();
        }
        break;
    }
    case 2:
    {
        const int gangle = -90;
        IO.drivebase.Turn(gangle);
        if (std::abs(IO.drivebase.GetGyroHeading() - gangle) < 5)
        {
            IO.drivebase.ResetEncoders();
            NextState();
        }
        break;
    }
    case 3:
    {
        const double encdist = 20.0;
        IO.drivebase.DriveForward(encdist, 0.95);
        if ((std::abs(IO.drivebase.GetEncoderPositionLeft() - encdist) < 3) && (std::abs(IO.drivebase.GetEncoderPositionRight() - encdist) < 3))
            ;
        {
            NextState();
        }
        break;
    }
    case 4:
    {
        const double elevHeight = 35.0;
        const double wristAngle = 30.0;
        IO.elevator.SetPosition(elevHeight);
        IO.wrist.SetAngle(wristAngle);
        if ((std::abs(IO.wrist.GetAngle() - wristAngle) < 3) && (std::abs(IO.elevator.GetDistance() - elevHeight) < 2))
            ;
        {
            NextState();
        }
        break;
    }
    case 5:
    {
        const double elevHeight = 0.0;
        const double wristAngle = 0.0;
        const double encdist = -10;
        IO.wrist.SetAngle(wristAngle);
        IO.drivebase.DriveForward(encdist);
        if (IO.wrist.GetAngle() < 20)
        {
            IO.elevator.SetPosition(elevHeight);
        }
        if ((std::abs(IO.wrist.GetAngle() - wristAngle) < 3) && (std::abs(IO.elevator.GetDistance() - elevHeight) < 2))
            ;
        {
            NextState();
        }
        break;
    }
    case 6:
    {
        const int gangle = -200;
        IO.drivebase.Turn(gangle);
        if (std::abs(IO.drivebase.GetGyroHeading() - gangle) < 5)
        {
            NextState();
        }
        break;
    }
    // case 3:
    // {
    //     IO.vision.CVMode(true);
    //     Vision::returnData dataDrop = IO.vision.Run();
    //     double error = dataDrop.cmd;

    //     if (dataDrop.distance >= 70 || error == -3.14)
    //     {
    //         IO.drivebase.Arcade(0, 0);
    //     }
    //     else
    //     {
    //         IO.drivebase.Arcade(0.3, -error);
    //     }
    //     if((std::abs(error) < 0.05) && dataDrop.distance >=70)
    //     {
    //         IO.vision.CVMode(false);
    //         NextState();
    //     }
    //     break;
    // }
    default:
        std::cout << "Ye" << std::endl;
        //IO.drivebase.Stop();
    }
}

// SmartDash updater
void AutoCargo::UpdateSmartdash()
{
    SmartDashboard::PutNumber("ENCODERR", IO.drivebase.GetEncoderPositionRight());
    SmartDashboard::PutNumber("auto state", m_state);
}