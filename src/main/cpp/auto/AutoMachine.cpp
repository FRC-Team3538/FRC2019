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
void AutoMachine::NextState(){
    m_state++;
    m_autoTimer.Reset();
    m_autoTimer.Start();
}

// Execute the program
void AutoMachine::Run()
{
    
    switch (m_state)
    {
    case 0:
    {
        //double fwd = 10;90,45,120
        //double rot = 0.00;
        //IO.drivebase.Arcade(fwd, rot);
        IO.drivebase.DriveForward(100);
        if (m_autoTimer.Get() > 3.0)
        {
            NextState();
        }
        break;
    }
    case 1:
    {
        double fwd = 0.00;
        double rot = 0.15;
        IO.drivebase.Arcade(fwd, rot);
        //IO.drivebase.Turn(45);
        if (m_autoTimer.Get() > 1.0)
        {
            IO.drivebase.ResetEncoders();
            NextState();
        }
        break;
    }
    case 2:
    {
        //double fwd = 10;90,45,120
        //double rot = 0.00;
        //IO.drivebase.Arcade(fwd, rot);
        IO.drivebase.DriveForward(90);
        if (m_autoTimer.Get() > 3.0)
        {
            NextState();
        }
        break;
    }
    default:
        IO.drivebase.Stop();
    }
}