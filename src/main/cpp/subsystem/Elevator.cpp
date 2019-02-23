#include "subsystem/Elevator.hpp"

#include <frc/smartdashboard/SmartDashboard.h>

// Configure Hardware Settings
Elevator::Elevator()
{
    // Default shifter state
    solenoidPTO.Set(false);

    // Invert motors if required
    motor1.SetInverted(false);
    motor2.SetInverted(false);

    // Link motors together
    motor2.Follow(motor1);

    // Encoder Configuration
    motor1.ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder);
    motor1.SetStatusFramePeriod(ctre::phoenix::motorcontrol::StatusFrameEnhanced::Status_3_Quadrature, 18);

    // PID Controller Configuration
    int absolutePosition = motor1.GetSelectedSensorPosition(0) & 0xFFF;

    int kPIDLoopIdx = 0;
    int kTimeoutMs = 30;

    motor1.SetSelectedSensorPosition(absolutePosition);

    /* choose the sensor and sensor direction */
    motor1.ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative);
    motor1.SetSensorPhase(true);

    /* set the peak and nominal outputs, 12V means full */
    motor1.ConfigNominalOutputForward(0);
    motor1.ConfigNominalOutputReverse(0);
    motor1.ConfigPeakOutputForward(1);
    motor1.ConfigPeakOutputReverse(-0.5);

    /* set closed loop gains in slot0 */
    motor1.Config_kF(kPIDLoopIdx, 0.0);
    motor1.Config_kP(kPIDLoopIdx, 0.1);
    motor1.Config_kI(kPIDLoopIdx, 0.0);
    motor1.Config_kD(kPIDLoopIdx, 0.0);
}

// Stop all motors
void Elevator::Stop()
{
    motor1.Set(0.0);
}

// Positive Speed is Up
void Elevator::Set(double speed)
{
    if (sensorOverride)
    {
        motor1.Set(ControlMode::PercentOutput, speed);
        return;
    }

    if (solenoidPTO.Get())
    {
        // Gantry Control
        if(speed < 0.0)
        {
            if(GetGanSwitchLeft() && GetGanSwitchRight())
            {
                motor1.Set(ControlMode::PercentOutput, speed);
            }
            else
            {
                Stop();
            }
        }
        else
        {
            motor1.Set(ControlMode::PercentOutput, speed);
        }
    }
    else
    {
        // Elevator Control
        if(speed != 0.0)
        {
            double pos = GetDistance();

            if ((pos > kMax || GetElvSwitchUpper() ) && speed > 0.0) {
                motor1.Set(ControlMode::PercentOutput, 0.0);
            }
            else if ((pos < kMin || GetElvSwitchLower() ) && speed < 0.0) {
                motor1.Set(ControlMode::PercentOutput, 0.0);
                ResetEnc();
            } 
            else if (pos < 15)
            {
                motor1.Set(ControlMode::PercentOutput, speed * 0.3);
            }
            else if (pos > 65)
            {
                motor1.Set(ControlMode::PercentOutput, speed * 0.3);
            }
            else
            {
                motor1.Set(ControlMode::PercentOutput, speed);
            }

            oneShot = false;
        }
        else if (!oneShot)
        {
            SetPosition(GetDistance());
            oneShot = true;
        }
    }
}

// Limit Switches
bool Elevator::GetElvSwitchUpper()
{
    return LimitElvSwitchUpper.Get();
}

bool Elevator::GetElvSwitchLower()
{
    return LimitElvSwitchLower.Get();
}

bool Elevator::GetGanSwitchLeft()
{
    return LimitSwitchGanLeft.Get();
}
bool Elevator::GetGanSwitchRight()
{
    return LimitSwitchGanRight.Get();
}

// Encoder Reset
void Elevator::ResetEnc()
{
    motor1.SetSelectedSensorPosition(0.0);
}

// Get Encoder value, inches from bottom
double Elevator::GetDistance()
{
    return kScaleFactor * motor1.GetSelectedSensorPosition();
}

// Closed loop control, inches from bottom
void Elevator::SetPosition(double pos)
{
    if (sensorOverride)
    {
        return;
    }

    motor1.Set(ControlMode::Position, pos / kScaleFactor);
    targetPos = pos;
}

void Elevator::ActivateGantry() 
{
    solenoidPTO.Set(true);
}

void Elevator::DeactivateGantry() 
{
    solenoidPTO.Set(false);
}

void Elevator::ToggleGantry() 
{
    solenoidPTO.Set(!solenoidPTO.Get());
}

void Elevator::ActivateSensorOverride()
{
    sensorOverride = true;
}

void Elevator::DeactivateSensorOverride()
{
    sensorOverride = false;
}

void Elevator::UpdateSmartdash()
{
    SmartDashboard::PutNumber("Elevator CMD", motor1.Get());
    //SmartDashboard::PutNumber("Elevator Raw", motor1.GetSensorCollection().GetQuadraturePosition()); // DO NOT USE!!!
    SmartDashboard::PutNumber("Elevator Raw", motor1.GetSelectedSensorPosition());

    SmartDashboard::PutBoolean("Elevator Sensor Override", sensorOverride);
    
    SmartDashboard::PutNumber("Elevator Pos", GetDistance());
    SmartDashboard::PutNumber("Elevator Pos Target", targetPos);

    //SmartDashboard::PutBoolean("Limit Switch Upper", GetElvSwitchUpper());
    SmartDashboard::PutBoolean("Limit Switch Elv Lower", GetElvSwitchLower());
    SmartDashboard::PutBoolean("Limit Switch Gan Left", GetGanSwitchLeft());
    SmartDashboard::PutBoolean("Limit Switch Gan Right", GetGanSwitchRight());

    SmartDashboard::PutBoolean("PTO Solenoid", solenoidPTO.Get());
    
}