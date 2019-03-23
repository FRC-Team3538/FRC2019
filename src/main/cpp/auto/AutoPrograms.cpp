#include "auto/AutoPrograms.hpp"

// Include all auto programs [List 1 of 3]
#include "auto/AutoLineCross.hpp"
#include "auto/AutoMachine.hpp"
#include "auto/AutoCargo.hpp"
#include "auto/HybridLeftNear.hpp"
#include "auto/HybridRightNear.hpp"

// Constructor requires a reference to the robot map
AutoPrograms::AutoPrograms(robotmap &IO) : IO(IO)
{

    // SmartDash Chooser [List 2 of 3]
    m_chooser.AddOption(AutoMachine::GetName(), AutoMachine::GetName());
    m_chooser.AddOption(AutoLineCross::GetName(), AutoLineCross::GetName());
    m_chooser.AddOption(AutoCargo::GetName(), AutoCargo::GetName());
    m_chooser.AddOption("Left Hybrid", "Left Hybrid");
    m_chooser.AddOption("Right Hybrid", "Right Hybrid");
    m_chooser.SetDefaultOption("0 - None", "0 - None");
}

// Initialize the selected auto program
void AutoPrograms::Init()
{
    // Get Selected Program from SmartDash Chooser
    std::string name = m_chooser.GetSelected();

    // Delete previously selected auto program
    delete m_autoProgram;
    m_autoProgram = NULL;

    // Create the Selected auto program [List 3 of 3]
    if (name == AutoLineCross::GetName())
    {
        m_autoProgram = new AutoLineCross(IO);
    }
    else if (name == AutoMachine::GetName())
    {
        m_autoProgram = new AutoMachine(IO);
    }
    else if (name == AutoCargo::GetName())
    {
        m_autoProgram = new AutoCargo(IO);
    }
    else if (name == "Left Hybrid")
    {
        m_autoProgram = new HybridLeftNear(IO);
    }
    else if (name == "Right Hybrid")
    {
        m_autoProgram = new HybridRightNear(IO);
    }
}

// Run the selected Auto Program
void AutoPrograms::Run()
{
    if (m_autoProgram)
    {
        m_autoProgram->Run();
    }
}

void AutoPrograms::SmartDash()
{
    SmartDashboard::PutData("Choose Auto", &m_chooser);
    std::string name = m_chooser.GetSelected();
    SmartDashboard::PutString("Selected Auto", name);
}