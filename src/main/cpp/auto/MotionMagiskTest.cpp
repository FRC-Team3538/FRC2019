#include "auto/MotionMagiskTest.hpp"


// Name for Smart Dash Chooser
std::string MotionMagiskTest::GetName()
{
    return "3 - MotionMagiskTest";
}

// Initialization
// Constructor requires a reference to the robot map
MotionMagiskTest::MotionMagiskTest(robotmap &IO) : IO(IO)
{
    m_state = 0;
    m_autoTimer.Reset();
    m_autoTimer.Start();
    IO.drivebase.Stop();
}

//State Machine
void MotionMagiskTest::NextState(){
    m_state++;
    m_autoTimer.Reset();
    m_autoTimer.Start();
}

// Execute the program
void MotionMagiskTest::Run()
{
    
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
        SmartDashboard::PutString("FACK", "FACK");

        IO.drivebase.setProfileSpd();
        if(!oneShot){
            
            IO.drivebase.magiskL1->start();
            IO.drivebase.magiskR1->start();
            oneShot = true;
        }
        break;
    }
    default:
        IO.drivebase.magiskL1->reset();
        IO.drivebase.magiskR1->reset();
        IO.drivebase.Stop();
        oneShot = false;
    }
}