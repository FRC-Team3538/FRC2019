#include "subsystem/Drivebase.h"

Drivebase::Drivebase()
{
    // Link motors together
    motorRight2.Follow(motorRight1);
    motorRight3.Follow(motorRight1);

    motorLeft2.Follow(motorLeft1);
    motorLeft3.Follow(motorLeft1);

    // Invert one side of the drive
    motorLeft1.SetInverted(false);
    motorLeft2.SetInverted(false);
    motorLeft3.SetInverted(false);

    motorRight1.SetInverted(true);
    motorRight2.SetInverted(true);
    motorRight3.SetInverted(true);

    // set default shifter state
    solenoidShifter.Set(false);
}

// Tanks Drive
void Drivebase::Tank(double left, double right)
{
    motorLeft1.Set(left);
    motorRight1.Set(right);
}

// Arcade Drive
void Drivebase::Arcade(double forward, double turn)
{
    motorLeft1.Set(forward - turn);
    motorRight1.Set(forward + turn);
}

// Stop!
void Drivebase::Stop()
{
    motorLeft1.StopMotor();
    motorRight1.StopMotor();
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
