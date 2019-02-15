#pragma once
#include "Waypoints.hpp"
#include "AutoInterface.hpp"
#include "frc/Notifier.h"
#include <ctre/Phoenix.h>

class MotionMagisk
{
  public:
    Waypoints waypoints;
    MotionProfileStatus _status;
    TalonSRX & _talon;

    double _pos = 0, _vel = 0, _heading = 0;
    int _state = 0;
    int _loopTimeout = -1;
    bool _bStart = false;
    SetValueMotionProfile _setValue = SetValueMotionProfile::Disable;
    static const int kMinPointsInTalon = 5;
    static const int kNumLoopsTimeout = 10;

    void PeriodicTask()
    {
        /* keep Talons happy by moving the points from top-buffer to bottom-buffer */
        _talon.ProcessMotionProfileBuffer();
    }

    Notifier _notifer;

    MotionMagisk(TalonSRX &talon) : _talon(talon), _notifer(&MotionMagisk::PeriodicTask, this)
    {
        /*
		 * since our MP is 10ms per point, set the control frame rate and the
		 * notifer to half that
		 */
        _talon.ChangeMotionControlFramePeriod(5);

        /* start our tasking */
        _notifer.StartPeriodic(0.005);
    }

    void reset()
    {
        /*
		 * Let's clear the buffer just in case user decided to disable in the
		 * middle of an MP, and now we have the second half of a profile just
		 * sitting in memory.
		 */
        _talon.ClearMotionProfileTrajectories();
        /* When we do re-enter motionProfile control mode, stay disabled. */
        _setValue = SetValueMotionProfile::Disable;
        /* When we do start running our state machine start at the beginning. */
        _state = 0;
        _loopTimeout = -1;
        /*
		 * If application wanted to start an MP before, ignore and wait for next
		 * button press
		 */
        _bStart = false;
    }

    /**
	 * Called every loop.
	 */
    void control()
    {

        /*
		 * track time, this is rudimentary but that's okay, we just want to make
		 * sure things never get stuck.
		 */
        if (_loopTimeout < 0)
        {
            /* do nothing, timeout is disabled */
        }
        else
        {
            /* our timeout is nonzero */
            if (_loopTimeout == 0)
            {
                /*
				 * something is wrong. Talon is not present, unplugged, breaker
				 * tripped
				 */
            }
            else
            {
                --_loopTimeout;
            }
        }

        /* first check if we are in MP mode */
        if (_talon.GetControlMode() != ControlMode::MotionProfile)
        {
            /*
			 * we are not in MP mode. We are probably driving the robot around
			 * using gamepads or some other mode.
			 */
            _state = 0;
            _loopTimeout = -1;
        }
        else
        {
            /*
			 * we are in MP control mode. That means: starting Mps, checking Mp
			 * progress, and possibly interrupting MPs if thats what you want to
			 * do.
			 */
            switch (_state)
            {
            case 0: /* wait for application to tell us to start an MP */
                if (_bStart)
                {
                    _bStart = false;

                    _setValue = SetValueMotionProfile::Disable;
                    startFilling();

                    /*
					 * MP is being sent to CAN bus, wait a small amount of time
					 */
                    _state = 1;
                    _loopTimeout = kNumLoopsTimeout;
                }
                break;
            case 1:
                /*
				 * wait for MP to stream to Talon, really just the first few
				 * points
				 */
                /* do we have a minimum numberof points in Talon */
                if (_status.btmBufferCnt > kMinPointsInTalon)
                {
                    /* start (once) the motion profile */
                    _setValue = SetValueMotionProfile::Enable;
                    /* MP will start once the control frame gets scheduled */
                    _state = 2;
                    _loopTimeout = kNumLoopsTimeout;
                }
                break;
            case 2: /* check the status of the MP */
                /*
				 * if talon is reporting things are good, keep adding to our
				 * timeout. Really this is so that you can unplug your talon in
				 * the middle of an MP and react to it.
				 */
                if (_status.isUnderrun == false)
                {
                    _loopTimeout = kNumLoopsTimeout;
                }
                /*
				 * If we are executing an MP and the MP finished, start loading
				 * another. We will go into hold state so robot servo's
				 * position.
				 */
                if (_status.activePointValid && _status.isLast)
                {
                    /*
					 * because we set the last point's isLast to true, we will
					 * get here when the MP is done
					 */
                    _setValue = SetValueMotionProfile::Hold;
                    _state = 0;
                    _loopTimeout = -1;
                }
                break;
            }

            /* Get the motion profile status every loop */
            _talon.GetMotionProfileStatus(_status);
            _heading = _talon.GetActiveTrajectoryPosition();
            _pos = _talon.GetActiveTrajectoryPosition();
            _vel = _talon.GetActiveTrajectoryVelocity();

            /* printfs and/or logging */
        }
    }

    int GetTrajectoryDuration(int durationMs)
    {
        /* lookup and return valid value */
        return durationMs;
    }

    void startFilling()
    {
        /* since this example only has one talon, just update that one */
        startFilling(waypoints.kMotionProfile, waypoints.kMotionProfileSz);
    }

    void startFilling(const double profile[291][3], const int totalCnt)
    {
        TrajectoryPoint point;
        _talon.ClearMotionProfileTrajectories();
        for (int i = 0; i < totalCnt; ++i)
        {
            double positionRot = profile[i][0];
            double velocityRPM = profile[i][1];

            /* for each point, fill our structure and pass it to API */
            point.position = positionRot * 4096;         //Convert Revolutions to Units
            point.velocity = velocityRPM * 4096 / 600.0; //Convert RPM to Units/100ms
            point.headingDeg = 0;                        /* future feature - not used in this example*/
            point.profileSlotSelect0 = 0;                /* which set of gains would you like to use [0,3]? */
            point.profileSlotSelect1 = 0;                /* future feature  - not used in this example - cascaded PID [0,1], leave zero */
            point.timeDur = GetTrajectoryDuration((int)profile[i][2]);
            point.zeroPos = false;
            if (i == 0)
                point.zeroPos = true; /* set this to true on the first point */

            point.isLastPoint = false;
            if ((i + 1) == totalCnt)
                point.isLastPoint = true; /* set this to true on the last point  */

            _talon.PushMotionProfileTrajectory(point);
        }
    }

    void start()
    {
        _bStart = true;
    }

    SetValueMotionProfile getSetValue()
    {
        return _setValue;
    }
};