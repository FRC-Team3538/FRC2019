#include "auto/AutoCargo.hpp"

#include <frc/smartdashboard/SmartDashboard.h>

// Name for Smart Dash Chooser
std::string AutoCargo::GetName()
{
    return "4 - AutoCargo";
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
        std::cout << "HEADINGV1 " << heading << std::endl;
        IO.drivebase.ResetEncoders();
        NextState();
        break;
    }
    case 1:
    {
        double encdist = 195.0;
        IO.drivebase.DriveForward(encdist, 0.95);
        if((IO.drivebase.GetEncoderPositionRight() + IO.drivebase.GetEncoderPositionLeft()) / 2 >= 30){
            IO.drivebase.forwardHeading = 30;
        }
        if ((std::abs(IO.drivebase.GetEncoderPositionLeft() - encdist + 6) < 3) && (std::abs(IO.drivebase.GetEncoderPositionRight() - encdist - 6) < 3))
        {
            NextState();
        }
        break;
    }
    // case 0:
    // {
    //     int encdist = 212;
    //     IO.drivebase.DriveForward(encdist);
    //     if (std::abs(IO.drivebase.GetEncoderPositionLeft() - encdist) < 5 && std::abs(IO.drivebase.GetEncoderPositionRight() - encdist) < 5)
    //     {
    //         NextState();
    //     }
    //     break;
    // }
    // case 1:
    // {
    //     int gangle = 90;
    //     IO.drivebase.Turn(gangle);
    //     if (std::abs(IO.drivebase.GetGyroHeading() - gangle) < 5)
    //     {
    //         IO.drivebase.ResetEncoders();
    //         NextState();
    //     }
    //     break;
    // }
    case 2:
    {
        int gangle = -90;
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
        IO.vision.CVMode(true);
        Vision::returnData dataDrop = IO.vision.Run();
        double error = dataDrop.cmd;

        if (dataDrop.distance >= 70 || error == -3.14)
        {
            IO.drivebase.Arcade(0, 0);
        }
        else
        {
            IO.drivebase.Arcade(0.3, -error);
        }
        if((std::abs(error) < 0.05) && dataDrop.distance >=70)
        {
            IO.vision.CVMode(false);
            NextState();
        }
        break;
    }
    // case 4:
    // {
    //     //Vision stuff here?
    //     //Richards vision stuff will go here eventually
    //     if (true)
    //     {
    //         NextState();
    //     }
    //     break;
    // }
    // case 5:
    // {
    //     int encdist = 30;
    //     IO.drivebase.DriveForward(encdist);
    //     if (std::abs(IO.drivebase.GetEncoderPositionLeft() - encdist) < 5 && std::abs(IO.drivebase.GetEncoderPositionRight() - encdist) < 5)
    //     {
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