#include "auto/AutoPrograms.h"

// Include all auto programs [List 1 of 3]
#include "auto/AutoLineCross.h"


// Constructor requires a reference to the robot map
AutoPrograms::AutoPrograms(robotmap &IO) : IO(IO) {

    // SmartDash Chooser [List 2 of 3]
    m_chooser.AddDefault("0 - None", "0 - None");
	m_chooser.AddObject(AutoLineCross::GetName(), AutoLineCross::GetName());
	SmartDashboard::PutData("AutoProgram", &m_chooser);
}

// Initialize the selected auto program
void AutoPrograms::Init()
{
    // Get Selected Program from SmartDash Chooser
    std::string name = m_chooser.GetSelected();

    // Delete previously selected program
    delete m_autoProgram;
    m_autoProgram = NULL;

    // Create the Selected Auto Program [List 3 of 3]
    if (name == AutoLineCross::GetName())
    {
        m_autoProgram = new AutoLineCross(IO);
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