#include "subsystem/Drivebase.h"

Drivebase::Drivebase()
{
    // Link motors together

    // Invert one side of the drive
    DriveLeft.SetInverted(false);

    DriveRight.SetInverted(true);

    // set default shifter state
    solenoidShifter.Set(false);
}

// Tanks Drive
void Drivebase::Tank(double left, double right)
{
    DriveLeft.Set(left);
    DriveRight.Set(right);
}

// Arcade Drive
void Drivebase::Arcade(double forward, double turn)
{
    DriveLeft.Set(forward - turn);
    DriveRight.Set(forward + turn);
}

// Stop!
void Drivebase::Stop()
{
    DriveLeft.StopMotor();
    DriveRight.StopMotor();
}

// Shift to High Gear
void Drivebase::SetHighGear()
{
    solenoidShifter.Set(false);
}

// Shift to Low Gear
void Drivebase::SetLowGear()
{
    solenoidShifter.Set(true);
}
