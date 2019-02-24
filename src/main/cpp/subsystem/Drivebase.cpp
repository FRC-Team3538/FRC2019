#include "subsystem/Drivebase.hpp"
#include "frc/Timer.h"

#include <ctre/Phoenix.h>
#include <frc/smartdashboard/SmartDashboard.h>

Drivebase::Drivebase()
{
    motorLeft1.ConfigFactoryDefault();
    motorLeft2.ConfigFactoryDefault();
    motorLeft3.ConfigFactoryDefault();
    motorRight1.ConfigFactoryDefault();
    motorRight2.ConfigFactoryDefault();
    motorRight3.ConfigFactoryDefault();

    motorLeft1.OverrideLimitSwitchesEnable(false);
    motorRight1.OverrideLimitSwitchesEnable(false);

    // set default shifter state
    solenoidShifter.Set(false);

    // Invert one side of the drive
    motorLeft1.SetInverted(true);
    motorLeft2.SetInverted(true);
    motorLeft3.SetInverted(true);

    motorRight1.SetInverted(false);
    motorRight2.SetInverted(false);
    motorRight3.SetInverted(false);

    DeactivateSensorOverride();

    // master > slaves
    motorLeft2.Follow(motorLeft1);
    motorLeft3.Follow(motorLeft1);

    motorRight2.Follow(motorRight1);
    motorRight3.Follow(motorRight1);

    // Encoder Feedback
    motorLeft1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, PIDind::primary);
    motorLeft1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_3_Quadrature, 18);

    motorRight1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, PIDind::primary);
    motorRight1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_3_Quadrature, 18);

    // motorLeft1.ConfigSelectedFeedbackCoefficient(-1.0);
    // motorRight1.ConfigSelectedFeedbackCoefficient(1.0);

    motorLeft1.SetSensorPhase(true);
    motorRight1.SetSensorPhase(true);

    motorLeft1.Config_kF(slots::Forward, 0.0);
    motorLeft1.Config_kP(slots::Forward, 0.1); //0.5
    motorLeft1.Config_kI(slots::Forward, 0.0);
    motorLeft1.Config_kD(slots::Forward, 0.04);

    motorRight1.Config_kF(slots::Forward, 0.0);
    motorRight1.Config_kP(slots::Forward, 0.1);
    motorRight1.Config_kI(slots::Forward, 0.0);
    motorRight1.Config_kD(slots::Forward, 0.04);

    motorLeft1.ConfigNominalOutputForward(0);
    motorLeft1.ConfigNominalOutputReverse(0);
    motorLeft1.ConfigPeakOutputForward(1);
    motorLeft1.ConfigPeakOutputReverse(-1);

    motorRight1.ConfigNominalOutputForward(0);
    motorRight1.ConfigNominalOutputReverse(0);
    motorRight1.ConfigPeakOutputForward(1);
    motorRight1.ConfigPeakOutputReverse(-1);

    // motorLeft1.ConfigSetParameter()

    //Remote Sensor
    motorLeft1.ConfigRemoteFeedbackFilter(0, RemoteSensorSource::RemoteSensorSource_Pigeon_Yaw, Remote0);
    motorRight1.ConfigRemoteFeedbackFilter(0, RemoteSensorSource::RemoteSensorSource_Pigeon_Yaw, Remote0);

    // motorLeft1.ConfigSensorTerm(SensorTerm::SensorTerm_Diff1, FeedbackDevice::QuadEncoder);
    // motorLeft1.ConfigSensorTerm(SensorTerm::SensorTerm_Diff0, FeedbackDevice::RemoteSensor0);
    // motorRight1.ConfigSensorTerm(SensorTerm::SensorTerm_Sum0, FeedbackDevice::QuadEncoder);
    // motorRight1.ConfigSensorTerm(SensorTerm::SensorTerm_Sum1, FeedbackDevice::RemoteSensor0);

    motorLeft1.ConfigAuxPIDPolarity(true);
    motorRight1.ConfigAuxPIDPolarity(true);

    motorLeft1.ConfigSelectedFeedbackSensor(FeedbackDevice::RemoteSensor0, PIDind::aux);
    motorRight1.ConfigSelectedFeedbackSensor(FeedbackDevice::RemoteSensor0, PIDind::aux);

    motorLeft1.Config_kF(slots::Turning, 0.0);
    motorLeft1.Config_kP(slots::Turning, 3.0); //.25
    motorLeft1.Config_kI(slots::Turning, 0.00);
    motorLeft1.Config_kD(slots::Turning, 0.0); //.02

    motorRight1.Config_kF(slots::Turning, 0.0);
    motorRight1.Config_kP(slots::Turning, 3.0);
    motorRight1.Config_kI(slots::Turning, 0.000);
    motorRight1.Config_kD(slots::Turning, 0.0);

    motorLeft1.SelectProfileSlot(slots::Forward, PIDind::primary);
    motorLeft1.SelectProfileSlot(slots::Turning, PIDind::aux);

    motorRight1.SelectProfileSlot(slots::Forward, PIDind::primary);
    motorRight1.SelectProfileSlot(slots::Turning, PIDind::aux);

    motorLeft1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_2_Feedback0, 5);
    motorRight1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_2_Feedback0, 5);

    motorLeft1.ConfigSetParameter(ParamEnum::ePIDLoopPeriod, 1, 0x00, PIDind::aux);
    motorLeft1.ConfigSetParameter(ParamEnum::ePIDLoopPeriod, 1, 0x00, PIDind::primary);
    motorRight1.ConfigSetParameter(ParamEnum::ePIDLoopPeriod, 1, 0x00, PIDind::aux);
    motorRight1.ConfigSetParameter(ParamEnum::ePIDLoopPeriod, 1, 0x00, PIDind::primary);
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
    solenoidShifter.Set(true);
}

// Shift to Low Gear
void Drivebase::SetLowGear()
{
    solenoidShifter.Set(false);
}

// Reset Encoders
void Drivebase::ResetEncoders()
{
    motorLeft1.SetSelectedSensorPosition(0);
    motorRight1.SetSelectedSensorPosition(0);
}

double Drivebase::GetEncoderPositionLeft()
{
    return motorLeft1.GetSelectedSensorPosition(0) * kScaleFactor;
}

double Drivebase::GetEncoderPositionRight()
{
    return motorRight1.GetSelectedSensorPosition(0) * kScaleFactor;
}

// Gyro
void Drivebase::ResetGyro()
{
    // navx.ZeroYaw();
    Hoothoot->SetFusedHeading(0.0);
    //navx.ResetDisplacement();
    //navx.Reset();
    std::cout << "reset" << std::endl;
}

double Drivebase::GetGyroHeading()
{
    double yaw = Hoothoot->GetFusedHeading();
    return yaw;
}

void Drivebase::DriveForward(double distance, double currentLimit)
{
    motorLeft1.ConfigNominalOutputForward(0);
    motorLeft1.ConfigNominalOutputReverse(0);
    motorLeft1.ConfigPeakOutputForward(currentLimit);
    motorLeft1.ConfigPeakOutputReverse(-currentLimit);

    motorRight1.ConfigNominalOutputForward(0);
    motorRight1.ConfigNominalOutputReverse(0);
    motorRight1.ConfigPeakOutputForward(currentLimit);
    motorRight1.ConfigPeakOutputReverse(-currentLimit);

    if (!oneShotAngle)
    {
        forwardHeading = GetGyroHeading() + 1;
        oneShotAngle = true;
    }

    double averageEncCnt = (GetEncoderPositionLeft() + GetEncoderPositionRight()) / 2;
    double error = distance - averageEncCnt;
    if (error < 24)
    {
        sumError_forward += error / 0.02;
    }
    else
    {
        sumError_forward = 0;
    }
    double deltaError = (error - prevError_forward) / 0.02;
    prevError_forward = error;

    double driveCommandForward = error * KP_FORWARD + sumError_forward * KI_FORWARD + KD_FORWARD * deltaError;


    double gyroAngle = GetGyroHeading();
    double errorRot = forwardHeading - gyroAngle;
    if (errorRot < 15) {
			sumError_rotation += errorRot / 0.02;
		} else {
			sumError_rotation = 0;
	}
    double deltaErrorRot = errorRot - prevError_rot;
    prevError_rot = error;

    double driveCommandRotation = errorRot * KP_ROTATION + KI_ROTATION * sumError_rotation + KD_ROTATION * deltaErrorRot;

    SmartDashboard::PutNumber("Forward!!!", driveCommandForward);
    SmartDashboard::PutNumber("NOTFORWARD!!!", driveCommandRotation);
    SmartDashboard::PutNumber("AlsoNotForward", forwardHeading);

    Arcade(driveCommandForward, driveCommandRotation);
}

void Drivebase::Turn(double heading)
{
    double errorRot = heading - GetGyroHeading();
    double deltaErrorRot = errorRot - prevError_rot;
    prevError_rot = errorRot;

    double driveCommandRotation = (errorRot * KP_ROTATION) + (KD_ROTATION * deltaErrorRot);

    Arcade(0, driveCommandRotation);
    // motorLeft1.Set(ControlMode::Position, 0, DemandType::DemandType_AuxPID, heading);
    // motorRight1.Set(ControlMode::Position, 0, DemandType::DemandType_AuxPID, heading);
}

void Drivebase::GlobalReset(){
    oneShotAngle = false;
    prevError_rotation = 0;
    prevError_forward = 0;
    sumError_forward = 0;
    prevError_rot = 0;
}

void Drivebase::ActivateSensorOverride()
{
    motorLeft1.ConfigPeakCurrentLimit(200);
    motorRight1.ConfigPeakCurrentLimit(200);
}

void Drivebase::DeactivateSensorOverride()
{
    motorLeft1.ConfigPeakCurrentLimit(60);
    motorRight1.ConfigPeakCurrentLimit(60);
}

// SmartDash updater
void Drivebase::UpdateSmartdash()
{
    SmartDashboard::PutNumber("DriveL", motorLeft1.Get());
    SmartDashboard::PutNumber("DriveR", motorRight1.Get());

    SmartDashboard::PutNumber("DriveEncL", GetEncoderPositionLeft());
    SmartDashboard::PutNumber("DriveEncR", GetEncoderPositionRight());

    //SmartDashboard::PutBoolean("DriveShifter", solenoidShifter.Get());

    SmartDashboard::PutNumber("GyroFused", GetGyroHeading());

/*
    SmartDashboard::PutNumber("TARGETrAUX", motorRight1.GetClosedLoopTarget(PIDind::aux));
    SmartDashboard::PutNumber("TARGETrPRIM", motorRight1.GetClosedLoopTarget(PIDind::primary));
    SmartDashboard::PutNumber("ERRORrAUX", motorRight1.GetClosedLoopError(PIDind::aux));
    SmartDashboard::PutNumber("ERRORrPRIM", motorRight1.GetClosedLoopError(PIDind::primary));
    SmartDashboard::PutNumber("POSrAUX", motorRight1.GetSelectedSensorPosition(PIDind::aux));
    SmartDashboard::PutNumber("POSrPRIM", motorRight1.GetSelectedSensorPosition(PIDind::primary));
    SmartDashboard::PutNumber("TARGETlAUX", motorLeft1.GetClosedLoopTarget(PIDind::aux));
    SmartDashboard::PutNumber("TARGETlPRIM", motorLeft1.GetClosedLoopTarget(PIDind::primary));
    SmartDashboard::PutNumber("ERRORlAUX", motorLeft1.GetClosedLoopError(PIDind::aux));
    SmartDashboard::PutNumber("ERRORlPRIM", motorLeft1.GetClosedLoopError(PIDind::primary));
    SmartDashboard::PutNumber("POSlAUX", motorLeft1.GetSelectedSensorPosition(PIDind::aux));
    SmartDashboard::PutNumber("POSlPRIM", motorLeft1.GetSelectedSensorPosition(PIDind::primary));
*/
}