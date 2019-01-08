#include "auto/AutoLineCrossEnc.h"

// Name for Smart Dash Chooser
std::string AutoLineCrossEnc::GetName()
{
    return "2 - AutoLineCrossEnc";
}

// Initialization
// Constructor requires a reference to the robot map
AutoLineCrossEnc::AutoLineCrossEnc(robotmap &IO) : IO(IO)
{
    m_state = 0;
    m_autoTimer.Reset();
    m_autoTimer.Start();
    IO.drivebase.Stop();
};

//State Machine
void AutoLineCrossEnc::NextState()
{
    m_state++;
    m_autoTimer.Reset();
    m_autoTimer.Start();
}

bool AutoLineCrossEnc::forward(double distance, double speed)
{ //BangBangSkeetSkeet //128 pulse 4 inch wheels direct
    const double wheelCircumference = 12.56637061;
    double rotations = IO.drivebase.GetEncPos("kRight") / 512;
    if(distance >= (rotations * wheelCircumference)){
        IO.drivebase.Arcade(speed, 0);
        return false;
    }
    else{
        IO.drivebase.Stop();    
        return true;
    }
}

// Execute the program
void AutoLineCrossEnc::Run()
{
    switch (m_state)
    {
    case 0:
    {
        if (forward(72,0.5) || m_autoTimer.Get() > 3.0)
        {
            NextState();
        }
        break;
    }
    default:
        IO.drivebase.Stop();
    }
}
