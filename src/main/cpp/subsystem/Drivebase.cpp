#include "subsystem/Drivebase.hpp"
#include "frc/Timer.h"

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
    motorLeft1.ConfigRemoteFeedbackFilter(motors::R1, RemoteSensorSource::RemoteSensorSource_TalonSRX_SelectedSensor, Remote0);
    motorRight1.ConfigRemoteFeedbackFilter(motors::L1, RemoteSensorSource::RemoteSensorSource_TalonSRX_SelectedSensor, Remote0);

    motorLeft1.ConfigSensorTerm(SensorTerm::SensorTerm_Diff1, FeedbackDevice::QuadEncoder);
    motorLeft1.ConfigSensorTerm(SensorTerm::SensorTerm_Diff0, FeedbackDevice::RemoteSensor0);
    motorRight1.ConfigSensorTerm(SensorTerm::SensorTerm_Sum0, FeedbackDevice::QuadEncoder);
    motorRight1.ConfigSensorTerm(SensorTerm::SensorTerm_Sum1, FeedbackDevice::RemoteSensor0);

    motorLeft1.ConfigAuxPIDPolarity(true);
    motorRight1.ConfigAuxPIDPolarity(true);

    motorLeft1.ConfigSelectedFeedbackSensor(FeedbackDevice::SensorDifference, PIDind::aux);
    motorRight1.ConfigSelectedFeedbackSensor(FeedbackDevice::SensorSum, PIDind::aux);

    motorLeft1.Config_kF(slots::Turning, 0.0);
	motorLeft1.Config_kP(slots::Turning, 0.25); //.25
	motorLeft1.Config_kI(slots::Turning, 0.0001);
	motorLeft1.Config_kD(slots::Turning, 0.25); //.02

    motorRight1.Config_kF(slots::Turning, 0.0);
	motorRight1.Config_kP(slots::Turning, 0.30);
	motorRight1.Config_kI(slots::Turning, 0.0001);
	motorRight1.Config_kD(slots::Turning, 0.02);

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
    navx.ZeroYaw();
    //navx.ResetDisplacement();
    //navx.Reset();
    std::cout << "reset" << std::endl;
}

double Drivebase::GetGyroHeading()
{
    double yaw = navx.GetYaw();
    return (yaw > 180) ? (yaw - 360) : (yaw) ;
}

void Drivebase::DriveForward(double distance, double currentLimit){
    motorLeft1.ConfigNominalOutputForward(0);
    motorLeft1.ConfigNominalOutputReverse(0);
    motorLeft1.ConfigPeakOutputForward(currentLimit);
    motorLeft1.ConfigPeakOutputReverse(-currentLimit);

    motorRight1.ConfigNominalOutputForward(0);
    motorRight1.ConfigNominalOutputReverse(0);
    motorRight1.ConfigPeakOutputForward(currentLimit);
    motorRight1.ConfigPeakOutputReverse(-currentLimit);
    distance /= kScaleFactor;
    motorLeft1.Set(ControlMode::Position, distance /*, DemandType::DemandType_AuxPID, 0*/);
    motorRight1.Set(ControlMode::Position, distance /*, DemandType::DemandType_AuxPID, 0*/);
}

void Drivebase::Turn(double degrees){
    // //17000 per turn
    // double pulses = (degrees / 360.0) * 17000.0;
    // motorLeft1.Set(ControlMode::Position, -pulses);
    // motorRight1.Set(ControlMode::Position, pulses);

        double sumError_rotation = 0;

		// For linear drive function
		double heading = degrees;
        // if(heading > 180){
        //     heading -= 360;
        // }

		// Use Gyro to drive straight
		double gyroAngle = GetGyroHeading() > 180 ? (GetGyroHeading()) - 360 : (GetGyroHeading());

		double error_rot = gyroAngle - heading;

        if (std::abs(error_rot) < 20) {
			sumError_rotation += (error_rot / 0.02);
		} else {
			sumError_rotation = 0;
		}

		// D Control
		double dError_rot = (error_rot - prevError_rotation) / 0.02; // [Inches/second]
		prevError_rotation = error_rot;

		double driveCommandRotation = (error_rot * KP_ROTATION) + (KD_ROTATION * dError_rot) + (sumError_rotation * KI_ROTATION);

		// dooo it!
		motorLeft1.Set(-driveCommandRotation);
        motorRight1.Set( driveCommandRotation);

        int ROTATION_TOLERANCE = 5;
        double settlingTime = 1.5;  
        Timer autoSettleTimer;      
		// // Allow for the robot to settle into position
		if (abs(error_rot) > ROTATION_TOLERANCE)
		{ 
            autoSettleTimer.Reset();
            autoSettleTimer.Start();
        }
		else if (autoSettleTimer.Get() > settlingTime)
        {

        }

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