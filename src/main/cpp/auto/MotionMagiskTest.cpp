#include "auto/MotionMagiskTest.hpp"

#include <frc/smartdashboard/SmartDashboard.h>

// Name for Smart Dash Chooser
std::string MotionMagiskTest::GetName()
{
    return "8 - MotionMagiskTest";
}

// Initialization
// Constructor requires a reference to the robot map
MotionMagiskTest::MotionMagiskTest(robotmap &IO) : IO(IO)
{
    m_state = 0;
    m_autoTimer.Reset();
    m_autoTimer.Start();
    IO.drivebase.Stop();
    IO.drivebase.ResetGyro();
    IO.drivebase.GlobalReset();
}

//State Machine
void MotionMagiskTest::NextState()
{
    m_state++;
    m_autoTimer.Reset();
    m_autoTimer.Start();
    IO.drivebase.ResetEncoders();
    IO.drivebase.GlobalReset();
}

// Execute the program
void MotionMagiskTest::Run()
{
    UpdateSmartdash();
    switch (m_state)
    {
    case 0:
    {
        IO.drivebase.DriveForward(0);
        if (m_autoTimer.Get() > 0.0)
        {
            NextState();
        }
        break;
    }
    case 1:
    {

        IO.drivebase.setProfileSpd();
        if(!oneShot){
            
            IO.drivebase.magiskR1->start();
            IO.drivebase.magiskL1->start();
            oneShot = true;
        }
        if(IO.drivebase.magiskR1->isDone() && IO.drivebase.magiskL1->isDone()){
            IO.drivebase.Arcade( 0.0, 0.0);
            NextState();
        }

        break;
    }
    default:
        oneShot = false;
        IO.drivebase.Arcade( 0.0, 0.0);
        IO.drivebase.magiskR1->reset();
        IO.drivebase.magiskL1->reset();   
    }
}

// SmartDash updater
void MotionMagiskTest::UpdateSmartdash()
{
    SmartDashboard::PutNumber("auto state", m_state);
}