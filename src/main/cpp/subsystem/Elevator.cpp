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
    motor1.ConfigPeakOutputReverse(-1);

    /* set closed loop gains in slot0 */
    motor1.Config_kF(kPIDLoopIdx, 0.0);
    motor1.Config_kP(kPIDLoopIdx, 0.2);
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
    if(speed < 0.0)
    {
        if(GetGanSwitchLeft() && GetGanSwitchRight())
        {
            motor1.Set(speed);
        }
        else
        {
            Stop();
        }
    }
    else
    {
        motor1.Set(speed);
    }
    
    
    /*double pos = GetDistance();

    if ((GetSwitchUpper() || pos > kMax) && speed > 0.0) 
    {
        motor1.Set(0.0);
    } 
    else if ((GetSwitchLower() || pos < kMin) && speed < 0.0) 
    {   
        // Zero the encoder on the lower switch
        motor1.Set(0.0);
        ResetEnc();
    } 
    else 
    {
        motor1.Set(speed);
    }*/
}

// Limit Switches
bool Elevator::GetSwitchUpper()
{
    return LimitSwitchEUpper.Get();
}

bool Elevator::GetSwitchLower1()
{
    return LimitSwitchELower.Get();
}

bool Elevator::GetSwitchLower2()
{
    return LimitSwitchELower2.Get();
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
    return kScaleFactor * motor1.GetSensorCollection().GetQuadraturePosition();
}

// Closed loop control, inches from bottom
void Elevator::SetPosition(double pos)
{
    //motor1.Set(ControlMode::Position, pos / kScaleFactor);
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
    SmartDashboard::PutNumber("Elevator CMD", motor1.GetSensorCollection().GetQuadraturePosition());

    SmartDashboard::PutBoolean(" Elevator Sensor Override", sensorOverride);
    
    SmartDashboard::PutNumber("Elevator Pos", GetDistance());
    SmartDashboard::PutNumber("Elevator Pos Target", targetPos);

    SmartDashboard::PutBoolean("Limit Switch Upper", GetSwitchUpper());
    SmartDashboard::PutBoolean("Limit Switch Lower", GetSwitchLower1());
    SmartDashboard::PutBoolean("Limit Switch Lower", GetSwitchLower2());
    SmartDashboard::PutBoolean("Limit Switch Gan Left", GetGanSwitchLeft());
    SmartDashboard::PutBoolean("Limit Switch Gan Right", GetGanSwitchRight());

    SmartDashboard::PutBoolean("PTO Solenoid", solenoidPTO.Get());
    
}