#include <iostream>
#include "subsystem/Drivebase.hpp"
#include <frc/smartdashboard/SmartDashboard.h>

using namespace std;

Drivebase::Drivebase()
{    
    // Invert one side of the drive
    DriveLeft.SetInverted(true);
    //DriveRight.SetInverted(false);


    // set default shifter state
    solenoidShifter.Set(false);

    motorRight1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);
    motorRight1.ConfigVelocityMeasurementPeriod(VelocityMeasPeriod::Period_25Ms, 0);
    motorRight1.ConfigVelocityMeasurementWindow(32, 0);
    motorRight1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_3_Quadrature, 18, 100);

    motorLeft1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);
    motorLeft1.ConfigVelocityMeasurementPeriod(VelocityMeasPeriod::Period_25Ms, 0);
    motorLeft1.ConfigVelocityMeasurementWindow(32, 0);
    motorLeft1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_3_Quadrature, 18, 100);

    //Right SRX
    /* lets grab the 360 degree position of the MagEncoder's absolute position */
    //int absolutePositionR1 = motorRight1.GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
    /* use the low level API to set the quad encoder signal */
    //motorRight1.SetSelectedSensorPosition(absolutePositionR1, kPIDLoopIdx,kTimeoutMs);

    /* choose the sensor and sensor direction */
    //motorRight1.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx,kTimeoutMs);
    //motorRight1.SetSensorPhase(true);

    /* set the peak and nominal outputs, 12V means full */
    //motorRight1.ConfigNominalOutputForward(0, kTimeoutMs);
    //motorRight1.ConfigNominalOutputReverse(0, kTimeoutMs);
    //motorRight1.ConfigPeakOutputForward(1, kTimeoutMs);
    //motorRight1.ConfigPeakOutputReverse(-1, kTimeoutMs);

    /* set closed loop gains in slot0 */
    //motorRight1.Config_kF(kPIDLoopIdx, 0.0, kTimeoutMs);
    //motorRight1.Config_kP(kPIDLoopIdx, 0.2, kTimeoutMs);
    //motorRight1.Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
    //motorRight1.Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

    //Left SRX
        /* lets grab the 360 degree position of the MagEncoder's absolute position */
    //int absolutePositionL1 = motorLeft1.GetSelectedSensorPosition(0) & 0xFFF; /* mask out the bottom12 bits, we don't care about the wrap arounds */
    /* use the low level API to set the quad encoder signal */
    //motorLeft1.SetSelectedSensorPosition(absolutePositionL1, kPIDLoopIdx,kTimeoutMs);

    /* choose the sensor and sensor direction */
   // motorLeft1.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx,kTimeoutMs);
    //motorLeft1.SetSensorPhase(true);

    /* set the peak and nominal outputs, 12V means full */
    //motorLeft1.ConfigNominalOutputForward(0, kTimeoutMs);
    //motorLeft1.ConfigNominalOutputReverse(0, kTimeoutMs);
    //motorLeft1.ConfigPeakOutputForward(1, kTimeoutMs);
    //motorLeft1.ConfigPeakOutputReverse(-1, kTimeoutMs);

    /* set closed loop gains in slot0 */
    //motorLeft1.Config_kF(kPIDLoopIdx, 0.0, kTimeoutMs);
    //motorLeft1.Config_kP(kPIDLoopIdx, 0.2, kTimeoutMs);
    //motorLeft1.Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
    //motorLeft1.Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

    motorLeft2.Follow(motorLeft1);
    motorLeft3.Follow(motorLeft1);
    motorRight2.Follow(motorRight1);
    motorRight3.Follow(motorRight1);
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
    if(slave == true)
    {
    
    //DriveRight.SetInverted(true);
    motorRight1.Follow(motorLeft1);
    motorRight2.Follow(motorRight1);
    motorRight3.Follow(motorRight1);
    
    } 
    cout << "Forward: " << forward << endl;
    DriveLeft.Set(forward - turn);
   // DriveRight.Set(forward + turn);
    
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

void Drivebase::Holonomic(double forward, double rotate, double strafe)
{
    double front_Left = forward - rotate + strafe;
    double front_Right = -(forward + rotate + strafe);
    double back_Left = forward - rotate - strafe;
    double back_Right = -(forward + rotate - strafe);

    double Magnitude = abs(forward) + abs(rotate) + abs(strafe);

    if (abs(front_Right) > Magnitude)
    {
        Magnitude = abs(front_Right);
    }
    if (abs(back_Left) > Magnitude)
    {
        Magnitude = abs(back_Left);
    }
    if (abs(back_Right) > Magnitude)
    {
        Magnitude = abs(back_Right);
    }

    if (Magnitude > 1)
    {
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

void Drivebase::UpdateSmartdash()
{
    std::string moL = "DriveLeft";
    std::string moR = "DriveRight";

    SmartDashboard::PutNumber(moL, motorLeft1.Get());
    SmartDashboard::PutNumber(moR, motorRight1.Get());

    //SmartDashboard::PutNumber("EncVelL (FeetPerSec)", motorLeft1.GetSensorCollection().GetQuadratureVelocity() / 4096);
    SmartDashboard::PutNumber("EncPosL", (double)motorLeft1.GetSensorCollection().GetQuadraturePosition() / 4096.0 * 6.0 * 3.14159265358979323);
    //SmartDashboard::PutNumber("EncVelR (FeetPerSec)", motorRight1.GetSensorCollection().GetQuadratureVelocity() / 4096);
    SmartDashboard::PutNumber("EncPosR", (double)motorRight1.GetSensorCollection().GetQuadraturePosition() / 4096.0 * 6.0 * 3.14159265358979323);
    SmartDashboard::PutNumber("Gyro Angle", navx.GetAngle());

    

    SmartDashboard::PutNumber("SolShifter", solenoidShifter.Get());
    SmartDashboard::PutNumber("GyroFused", navx.GetFusedHeading());
}

void Drivebase::Log()
{
    //IO.log.Log("Drivebase.L1.get", motorLeft1.Get());
    //IO.log.Log("Drivebase.R1.get", motorRight1.Get());
}

double Drivebase::EncPosL(){
    return (motorLeft1.GetSensorCollection().GetQuadraturePosition() / 4096.0 * 6.0 * 3.1415926535897932);
}

double Drivebase::EncPosR(){
    return (motorRight1.GetSensorCollection().GetQuadraturePosition() / 4096.0 * 6.0 * 3.1415926535897932);
}

void Drivebase::ResetEnc(){
    motorLeft1.SetSelectedSensorPosition(0);
    motorRight1.SetSelectedSensorPosition(0);
}

double Drivebase::GetGyroAngle(){
    return navx.GetAngle();
}
