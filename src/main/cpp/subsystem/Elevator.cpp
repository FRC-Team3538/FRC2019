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
    motor1.ConfigPeakOutputReverse(-0.25);

    DeactivateGantry();

    /* set closed loop gains in slot0 */
    motor1.Config_kF(kPIDLoopIdx, 0.0);
    motor1.Config_kP(kPIDLoopIdx, 0.15);  //0.15  0.125
    motor1.Config_kI(kPIDLoopIdx, 0.000); // 0.0005
    motor1.Config_kD(kPIDLoopIdx, -1.0);  //-1.0

    motor1.Config_IntegralZone(kPIDLoopIdx, (5 / kScaleFactor));

    motor1.ConfigClosedloopRamp(0.2);
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
        if (speed < 0.0) //Currently blocking going down
        {
            if (GetGanSwitchLeft() || GetGanSwitchRight())
            {
                Stop();
            }
            else
            {
                motor1.Set(ControlMode::PercentOutput, speed);
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
        if (speed != 0.0)
        {
            motor1.SetIntegralAccumulator(0);
            if (!oneShotOutput)
            {
                motor1.ConfigPeakOutputReverse(-0.25);
                oneShotOutput = true;
            }

            double pos = GetDistance();

            //     motor1.Set(ControlMode::PercentOutput, 0.0);
            // if ((/*pos > kMax ||*/ GetElvSwitchUpper() ) && speed > 0.0) {
            // }
            if ((/*pos < kMin ||*/ GetElvSwitchLower()) && speed < 0.0)
            {
                motor1.Set(ControlMode::PercentOutput, 0.0);
                ResetEnc();
            }
            // else if (pos < 15)
            // {
            //     motor1.Set(ControlMode::PercentOutput, speed * 0.3);
            // }
            // else if (pos > 65)
            // {
            //     motor1.Set(ControlMode::PercentOutput, speed * 0.3);
            // }
            else
            {
                motor1.Set(ControlMode::PercentOutput, speed);
            }
            prevElevSpd = motor1.GetSelectedSensorVelocity() * kScaleFactor * 10.0;

            oneShot = false;
        }
        else
        {
            // if ((((motor1.GetSelectedSensorVelocity() * kScaleFactor * 10.0) > 4.0) || ((motor1.GetSelectedSensorVelocity() * kScaleFactor * 10.0) < -15)) && ( !oneShot ))
            // { //Greater than 2 inch / sec
            //     motor1.Set(ControlMode::PercentOutput, 0);
            // }
            if (!oneShot)
            {
                motor1.ConfigPeakOutputReverse(-0.25);
                oneShotOutput = false;
                SetPosition(GetDistance());

                oneShot = true;
            }

            if (abs(targetPos - GetDistance()) < 0.5)
            {
                motor1.Set(ControlMode::PercentOutput, 0.11);
                oneShotPID = false;
            }
            else if(!oneShotPID)
            {
                SetPosition(targetPos);
                oneShotPID = true;
            }
        }
    }
}

// Limit Switches

// Returns true if pressed
bool Elevator::GetElvSwitchLeft()
{
    return !LimitSwitchElvLeft.Get();
}

bool Elevator::GetElvSwitchRight()
{
    return !LimitSwitchElvRight.Get();
}

bool Elevator::GetElvSwitchLower()
{
    return GetElvSwitchLeft() || GetElvSwitchRight();
}

bool Elevator::GetGanSwitchLeft()
{
    return !LimitSwitchGanLeft.Get();
}

bool Elevator::GetGanSwitchRight()
{
    return !LimitSwitchGanRight.Get();
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
    motor1.ConfigPeakOutputReverse(-1.0);
}

void Elevator::DeactivateGantry()
{
    solenoidPTO.Set(false);
    motor1.ConfigPeakOutputReverse(-0.25);
}

void Elevator::ToggleGantry()
{
    motor1.ConfigPeakOutputReverse((!solenoidPTO.Get() ? -1.0 : -0.25));
    solenoidPTO.Set(!solenoidPTO.Get());
}

bool Elevator::GetGantryActivated()
{
    return solenoidPTO.Get();
}

void Elevator::ActivateSensorOverride()
{
    sensorOverride = true;
}

void Elevator::DeactivateSensorOverride()
{
    sensorOverride = false;
}

void Elevator::SetServo(double setPoint)
{
    if (setPoint != 118)
    {
        armRetention.SetAngle(setPoint);
    }
    else
    {
        solenoidPTO.Get() ? armRetention.SetAngle(servoSetPoints::max) : armRetention.SetAngle(servoSetPoints::min);
    }
}

void Elevator::LevelRobot(double pitch)
{
    double error = pitch;
    double cmd = error * kPGan;
    if ((GetGanSwitchLeft() || GetGanSwitchRight()) && cmd < 0)
    {
        motor1.Set(0.0);
    }
    else
    {
        motor1.Set(cmd);
    }
}

void Elevator::UpdateSmartdash()
{
    SmartDashboard::PutNumber("Elevator CMD", motor1.GetMotorOutputPercent());
    SmartDashboard::PutNumber("Velocity", (motor1.GetSelectedSensorVelocity() * kScaleFactor * 10.0));
    //SmartDashboard::PutNumber("Elevator Raw", motor1.GetSensorCollection().GetQuadraturePosition()); // DO NOT USE!!!
    SmartDashboard::PutNumber("Elevator Raw", motor1.GetSelectedSensorPosition());

    SmartDashboard::PutBoolean("Elevator Sensor Disabled", sensorOverride);

    SmartDashboard::PutNumber("Elevator Pos", GetDistance());
    SmartDashboard::PutNumber("Elevator Pos Target", targetPos);

    SmartDashboard::PutBoolean("Limit Sw Elv Left", GetElvSwitchLeft());
    SmartDashboard::PutBoolean("Limit Sw Elv Right", GetElvSwitchRight());
    SmartDashboard::PutBoolean("Limit Sw Gan Left", GetGanSwitchLeft());
    SmartDashboard::PutBoolean("Limit Sw Gan Right", GetGanSwitchRight());

    SmartDashboard::PutBoolean("PTO Solenoid", solenoidPTO.Get());
}