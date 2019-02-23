#include "subsystem/Wrist.hpp"

#include <frc/smartdashboard/SmartDashboard.h>

// Configure Hardware Settings
Wrist::Wrist()
{
    motor1.ConfigFactoryDefault();

    motor1.SetInverted(false);
    motor1.SetSensorPhase(true);
    motor1.ConfigPeakCurrentLimit(5);
    motor1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder);
    motor1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_3_Quadrature, 18);

    int absolutePosition = motor1.GetSelectedSensorPosition(0) & 0xFFF;
    motor1.SetSelectedSensorPosition(absolutePosition);

    motor1.Config_kF(0, 0.0, 0);
	motor1.Config_kP(0, 2.0, 0);
	motor1.Config_kI(0, 0.0, 0);
	motor1.Config_kD(0, 0.0, 0);

    motor1.ConfigNominalOutputForward(0);
    motor1.ConfigNominalOutputReverse(0);
    motor1.ConfigPeakOutputForward(0.3);
    motor1.ConfigPeakOutputReverse(-0.4);
    // TODO: Setup angle sensor
}

// Stop all motors
void Wrist::Stop()
{
    motor1.Set(0.0);
}

// Positive speed is up
void Wrist::SetSpeed(double speed)
{
    if (sensorOverride)
    {
        motor1.Set(speed);
        return;
    }

    if(speed != 0.0)
    {
        double pos = GetAngle();

        if ((pos > kMax || GetSwitchUpper() ) && speed > 0.0) {
            motor1.Set(0.0);
        }
        else if ((pos < kMin || GetSwitchLower() ) && speed < 0.0) {
            motor1.Set(0.0);
            ResetEnc();
        } 
        else if (pos < 15)
        {
            motor1.Set(speed * 0.3);
        }
        else if (pos > 110)
        {
            motor1.Set(speed * 0.3);
        }
        else
        {
            motor1.Set(speed);
        }

        oneShot = false;
    }
    else if (!oneShot)
    {
        SetAngle(GetAngle());
        oneShot = true;
    }
    
}

// Limit Switches
bool Wrist::GetSwitchUpper()
{
    return LimitSwitchUpper.Get();
}

bool Wrist::GetSwitchLower()
{
    return LimitSwitchUpper.Get();
}

// Closed loop control
void Wrist::SetAngle(double angle)
{
    if (sensorOverride)
    {
        return;
    }

    wristPosTarget = angle / kScale;
    motor1.Set(ControlMode::Position, wristPosTarget);
}
                                                                 
double Wrist::GetAngle()
{
    return motor1.GetSelectedSensorPosition(0) * kScale;
}

void Wrist::ResetEnc()
{
    motor1.SetSelectedSensorPosition(0.0);
}

void Wrist::ActivateSensorOverride()
{
    sensorOverride = true;
}

void Wrist::DeactivateSensorOverride()
{
    sensorOverride = false;
}

void Wrist::UpdateSmartdash()
{
    SmartDashboard::PutNumber("Wrist Motor", motor1.Get());
    SmartDashboard::PutNumber("Wrist Angle", GetAngle());
    SmartDashboard::PutNumber("Wrist Angle Target", wristPosTarget);
    SmartDashboard::PutBoolean("Wrist Sensor Override", sensorOverride);
}