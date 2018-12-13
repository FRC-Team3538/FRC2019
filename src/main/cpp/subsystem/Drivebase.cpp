#include "subsystem/Drivebase.h"
#include <SmartDashboard/SmartDashboard.h>

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
    solenoidShifter.Set(true);
}

// Shift to Low Gear
void Drivebase::SetLowGear()
{
    solenoidShifter.Set(false);
}

void Drivebase::Holonomic(double forward, double rotate, double strafe){
    double front_Left = forward - rotate + strafe;
    double front_Right = -(forward + rotate + strafe);
    double back_Left = forward - rotate - strafe;
    double back_Right = -(forward + rotate - strafe);
    SmartDashboard::PutNumber("FrontLeft", front_Left);
    SmartDashboard::PutNumber("FrontRight", front_Right);
    SmartDashboard::PutNumber("BackLeft", back_Left);
    SmartDashboard::PutNumber("BackRight", back_Right);
    double Magnitude = abs(forward) + abs(rotate) + abs(strafe);

    if(abs(front_Right) > Magnitude){
        Magnitude = abs(front_Right);
    }
    if(abs(back_Left) > Magnitude){
        Magnitude = abs(back_Left);
    }
    if(abs(back_Right) > Magnitude){
        Magnitude = abs(back_Right);
    }

    if(Magnitude > 1){
        front_Left /= Magnitude;
        front_Right /= Magnitude;
        back_Left /= Magnitude;
        back_Right /= Magnitude;
    }
    frontLeft.Set(front_Left);
    frontRight.Set(front_Right);
    backLeft.Set(back_Left);
    backRight.Set(back_Right);
}
