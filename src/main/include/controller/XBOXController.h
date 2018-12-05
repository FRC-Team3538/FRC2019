/*----------------------------------------------------------------------------*/
/* Copyright (c) 2016-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//Needs to be Changed to xbox xbox controlls
#pragma once

#include "GenericHID.h"

namespace frc {

/**
 * Handle input from XBOX controllers connected to the Driver Station.
 *
 * This class handles input that comes from the Driver Station. Each time a
 * value is requested the most recent value is returned. There is a single class
 * instance for each controller and the mapping of ports to hardware buttons
 * depends on the code in the Driver Station.
 */
class XBOXController : public GenericHID {
 public:
  explicit XBOXController(int port);
  virtual ~XBOXController() = default;

  XBOXController(const XBOXController&) = delete;
  XBOXController& operator=(const XBOXController&) = delete;

  double GetX(JoystickHand hand) const override;
  double GetY(JoystickHand hand) const override;
  double GetTriggerAxis(JoystickHand hand) const;

  bool GetBumper(JoystickHand hand) const;
  bool GetBumperPressed(JoystickHand hand);
  bool GetBumperReleased(JoystickHand hand);

  bool GetStickButton(JoystickHand hand) const;
  bool GetStickButtonPressed(JoystickHand hand);
  bool GetStickButtonReleased(JoystickHand hand);

  bool GetCrossButton() const;
  bool GetCrossButtonPressed();
  bool GetCrossButtonReleased();

  bool GetCircleButton() const;
  bool GetCircleButtonPressed();
  bool GetCircleButtonReleased();

  bool GetSquareButton() const;
  bool GetSquareButtonPressed();
  bool GetSquareButtonReleased();

  bool GetTriangleButton() const;
  bool GetTriangleButtonPressed();
  bool GetTriangleButtonReleased();

  bool GetScreenShotButton() const;
  bool GetScreenShotButtonPressed();
  bool GetScreenShotButtonReleased();

  bool GetOptionsButton() const;
  bool GetOptionsButtonPressed();
  bool GetOptionsButtonReleased();

  bool GetPSButton() const;
  bool GetPSButtonPressed();
  bool GetPSButtonReleased();


 private:
  enum class Button {
    kBumperLeft = 5,
    kBumperRight = 6,
    kStickLeft = 9,
    kStickRight = 10,
    kCross = 1,
    kCircle = 2,
    kSquare = 3,
    kTriangle = 4,
    kScreenShot = 7,
    kOptions = 8,
    kPS = 9
  };
};

}  // namespace frc
