#include "subsystem/Wrist.hpp"

#include <frc/smartdashboard/SmartDashboard.h>

// Configure Hardware Settings
Wrist::Wrist()
{
    motor1.ConfigFactoryDefault();

    motor1.SetInverted(false);
    motor1.SetSensorPhase(true);
    motor1.ConfigPeakCurrentLimit(5);
    motor1.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
    motor1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_2_Feedback0, 18);

    // int absolutePosition = motor1.GetSelectedSensorPosition(0) & 0xFFF;
    // motor1.SetSelectedSensorPosition(absolutePosition);

    motor1.Config_kF(0, 0.0, 0);
    motor1.Config_kP(0, 0.5, 0); //0.5
    motor1.Config_kI(0, 0.0, 0);
    motor1.Config_kD(0, 0.0, 0);

    motor1.ConfigNominalOutputForward(0);
    motor1.ConfigNominalOutputReverse(0);

    motor1.ConfigPeakOutputForward(1.0);
    motor1.ConfigPeakOutputReverse(-1.0);

    motor1.ConfigReverseSoftLimitThreshold(kMin / kScale);
    motor1.ConfigForwardSoftLimitThreshold(kMax / kScale);

    DeactivateSensorOverride();
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

    if (speed != 0.0)
    {
        double pos = GetAngle();

        if (GetSwitchUpper() && speed > 0.0)
        {
            motor1.Set(0.0);
        }
        else if (GetSwitchLower() && speed < 0.0)
        {
            motor1.Set(0.0);
            ResetEnc();
        }
        else
        {
            motor1.Set(speed);
        }

        oneShot = false;
        return;
    }
    else if (!oneShot)
    {
        motor1.Set(0);
        // SetAngle(GetAngle());
        // No need to hold angle. Backdrive is off the chains
        oneShot = true;
    }
}

// Limit Switches
bool Wrist::GetSwitchUpper()
{
    //Sees if Talon "Exists"
    if (motor1.GetFirmwareVersion() == -1)
    {
        return false;
    }   
    return motor1.GetSensorCollection().IsFwdLimitSwitchClosed();
}

bool Wrist::GetSwitchLower()
{
    //Sees if Talon "Exists"
    if (motor1.GetFirmwareVersion() == -1)
    {
        return false;
    } 
    return motor1.GetSensorCollection().IsRevLimitSwitchClosed();
}

// Closed loop control
void Wrist::SetAngle(double angle)
{
    if (sensorOverride)
    {
        return;
    }

    motor1.Set(ControlMode::Position, (angle / kScale));

    // For smartdash
    wristPosTarget = angle;
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

    motor1.ConfigReverseSoftLimitEnable(false);
    motor1.ConfigForwardSoftLimitEnable(false);

    sensorOverride = true;
}

void Wrist::DeactivateSensorOverride()
{
    motor1.ConfigReverseSoftLimitEnable(false); // true
    motor1.ConfigForwardSoftLimitEnable(false); // true

    sensorOverride = false;
}

void Wrist::ActivateLimitSwitchOverride()
{
    motor1.ConfigReverseSoftLimitEnable(true);
    motor1.ConfigForwardSoftLimitEnable(true);

    sensorOverride = true;
}

void Wrist::UpdateSmartdash()
{
    SmartDashboard::PutNumber("Wrist Motor CMD", motor1.Get());
    SmartDashboard::PutNumber("Wrist Motor Raw", motor1.GetSelectedSensorPosition());
    SmartDashboard::PutNumber("Wrist Angle", GetAngle());
    SmartDashboard::PutNumber("Wrist Angle Target", wristPosTarget);
    SmartDashboard::PutBoolean("Wrist Sensor Disabled", sensorOverride);
    SmartDashboard::PutBoolean("Wrist Limit Switch Lower", GetSwitchLower());
    SmartDashboard::PutBoolean("Wrist Limit Switch Upper", GetSwitchUpper());
}

double Wrist::GetTargetAngle(){
    return motor1.GetClosedLoopTarget(0);
}