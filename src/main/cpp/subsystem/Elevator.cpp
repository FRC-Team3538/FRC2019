#include "subsystem/Elevator.hpp"

// Configure Hardware Settings
Elevator::Elevator()
{
    motor1.SetInverted(true);
    motor2.SetInverted(false);

    motor1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, 0);
    motor1.ConfigVelocityMeasurementPeriod(VelocityMeasPeriod::Period_25Ms, 0);
    motor1.ConfigVelocityMeasurementWindow(32, 0);
    motor1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_3_Quadrature, 3, 100);

    int absolutePosition = motor1.GetSelectedSensorPosition(0) & 0xFFF;
    int kPIDLoopIdx = 0;
    int kTimeoutMs = 30;

		motor1.SetSelectedSensorPosition(absolutePosition, kPIDLoopIdx,
				kTimeoutMs);

		/* choose the sensor and sensor direction */
		motor1.ConfigSelectedFeedbackSensor(
				FeedbackDevice::CTRE_MagEncoder_Relative, kPIDLoopIdx,
				kTimeoutMs);
		motor1.SetSensorPhase(true);

		/* set the peak and nominal outputs, 12V means full */
		motor1.ConfigNominalOutputForward(0, kTimeoutMs);
		motor1.ConfigNominalOutputReverse(0, kTimeoutMs);
		motor1.ConfigPeakOutputForward(1, kTimeoutMs);
		motor1.ConfigPeakOutputReverse(-1, kTimeoutMs);

		/* set closed loop gains in slot0 */
		motor1.Config_kF(kPIDLoopIdx, 0.0, kTimeoutMs);
		motor1.Config_kP(kPIDLoopIdx, 0.1, kTimeoutMs);
		motor1.Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
		motor1.Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);
}

void Elevator::Stop()
{
    motors.Set(0.0);
}

//Positive Speed is intaking
void Elevator::Set(double speed)
{
    if (LimitSwitchUpper.Get() == false && speed > 0.0) {
        motors.Set(0.0);
    } else if (LimitSwitchLower.Get() == false && speed < 0.0) {
        motors.Set(0.0);
        resetEnc();
    } else {
        motors.Set(speed);
    }
}

double Elevator::GetDistance()
{
    double elevDistance = motor1.GetSensorCollection().GetQuadraturePosition();
    double distance = elevDistance * ((45 - 9.375) / 31196);
     /*
        9 3/8   0
        19 15/16    9,287
        45  31,196
     */
    return distance;
}

void Elevator::resetEnc()
{
    motor1.SetSelectedSensorPosition(0.0);
}

void Elevator::setPosition(double pos)
{
    pos = (pos / ((45 - 9.375) / 31196));
    motor1.Set(ControlMode::Position, pos);
}

void Elevator::UpdateSmartdash()
{
    SmartDashboard::PutNumber("Elevator CMD", motor1.GetSensorCollection().GetQuadraturePosition());
    SmartDashboard::PutNumber("Elevator Distance", GetDistance());
    SmartDashboard::PutBoolean("Limit Switch Upper", LimitSwitchUpper.Get());
    SmartDashboard::PutBoolean("Limit Switch Lower", LimitSwitchLower.Get());
}