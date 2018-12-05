/*----------------------------------------------------------------------------*/
/* Copyright (c) 2016-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

//needs to be changed to xbox controlls
#include <controller/XBOXController.h>

#include <HAL/HAL.h>

using namespace frc;

/**
 * Construct an instance of a PS4 controller.
 *
 * The controller index is the USB port on the Driver Station.
 *
 * @param port The port on the Driver Station that the controller is plugged
 *             into (0-5).
 */
XBOXController::XBOXController(int port) : GenericHID(port) {
  // HAL_Report(HALUsageReporting::kResourceType_XBOXController, port);
  HAL_Report(HALUsageReporting::kResourceType_Joystick, port);
}

/**
 * Get the X axis value of the controller.
 *
 * @param hand Side of controller whose value should be returned.
 */
double XBOXController::GetX(JoystickHand hand) const {
  if (hand == kLeftHand) {
    return GetRawAxis(0);
  } else {
    return GetRawAxis(4);
  }
}

/**
 * Get the Y axis value of the controller.
 *
 * @param hand Side of controller whose value should be returned.
 */
double XBOXController::GetY(JoystickHand hand) const {
  if (hand == kLeftHand) {
    return GetRawAxis(1);
  } else {
    return GetRawAxis(5);
  }
}

/**
 * Get the trigger axis value of the controller.
 *
 * @param hand Side of controller whose value should be returned.
 */
double XBOXController::GetTriggerAxis(JoystickHand hand) const {
  if (hand == kLeftHand) {
    return GetRawAxis(2);
  } else {
    return GetRawAxis(3);
  }
}

/**
 * Read the value of the bumper button on the controller.
 *
 * @param hand Side of controller whose value should be returned.
 */
bool XBOXController::GetBumper(JoystickHand hand) const {
  if (hand == kLeftHand) {
    return GetRawButton(static_cast<int>(Button::kBumperLeft));
  } else {
    return GetRawButton(static_cast<int>(Button::kBumperRight));
  }
}

/**
 * Whether the bumper was pressed since the last check.
 *
 * @param hand Side of controller whose value should be returned.
 * @return Whether the button was pressed since the last check.
 */
bool XBOXController::GetBumperPressed(JoystickHand hand) {
  if (hand == kLeftHand) {
    return GetRawButtonPressed(static_cast<int>(Button::kBumperLeft));
  } else {
    return GetRawButtonPressed(static_cast<int>(Button::kBumperRight));
  }
}

/**
 * Whether the bumper was released since the last check.
 *
 * @param hand Side of controller whose value should be returned.
 * @return Whether the button was released since the last check.
 */
bool XBOXController::GetBumperReleased(JoystickHand hand) {
  if (hand == kLeftHand) {
    return GetRawButtonReleased(static_cast<int>(Button::kBumperLeft));
  } else {
    return GetRawButtonReleased(static_cast<int>(Button::kBumperRight));
  }
}

/**
 * Read the value of the stick button on the controller.
 *
 * @param hand Side of controller whose value should be returned.
 * @return The state of the button.
 */
bool XBOXController::GetStickButton(JoystickHand hand) const {
  if (hand == kLeftHand) {
    return GetRawButton(static_cast<int>(Button::kStickLeft));
  } else {
    return GetRawButton(static_cast<int>(Button::kStickRight));
  }
}

/**
 * Whether the stick button was pressed since the last check.
 *
 * @param hand Side of controller whose value should be returned.
 * @return Whether the button was pressed since the last check.
 */
bool XBOXController::GetStickButtonPressed(JoystickHand hand) {
  if (hand == kLeftHand) {
    return GetRawButtonPressed(static_cast<int>(Button::kStickLeft));
  } else {
    return GetRawButtonPressed(static_cast<int>(Button::kStickRight));
  }
}

/**
 * Whether the stick button was released since the last check.
 *
 * @param hand Side of controller whose value should be returned.
 * @return Whether the button was released since the last check.
 */
bool XBOXController::GetStickButtonReleased(JoystickHand hand) {
  if (hand == kLeftHand) {
    return GetRawButtonReleased(static_cast<int>(Button::kStickLeft));
  } else {
    return GetRawButtonReleased(static_cast<int>(Button::kStickRight));
  }
}

/**
 * Read the value of the Cross button on the controller.
 *
 * @return The state of the button.
 */
bool XBOXController::GetCrossButton() const {
  return GetRawButton(static_cast<int>(Button::kCross));
}

/**
 * Whether the Cross button was pressed since the last check.
 *
 * @return Whether the button was pressed since the last check.
 */
bool XBOXController::GetCrossButtonPressed() {
  return GetRawButtonPressed(static_cast<int>(Button::kCross));
}

/**
 * Whether the Cross button was released since the last check.
 *
 * @return Whether the button was released since the last check.
 */
bool XBOXController::GetCrossButtonReleased() {
  return GetRawButtonReleased(static_cast<int>(Button::kCross));
}

/**
 * Read the value of the Circle button on the controller.
 *
 * @return The state of the button.
 */
bool XBOXController::GetCircleButton() const {
  return GetRawButton(static_cast<int>(Button::kCircle));
}

/**
 * Whether the Circle button was pressed since the last check.
 *
 * @return Whether the button was pressed since the last check.
 */
bool XBOXController::GetCircleButtonPressed() {
  return GetRawButtonPressed(static_cast<int>(Button::kCircle));
}

/**
 * Whether the Circle button was released since the last check.
 *
 * @return Whether the button was released since the last check.
 */
bool XBOXController::GetCircleButtonReleased() {
  return GetRawButtonReleased(static_cast<int>(Button::kCircle));
}

/**
 * Read the value of the Square button on the controller.
 *
 * @return The state of the button.
 */
bool XBOXController::GetSquareButton() const {
  return GetRawButton(static_cast<int>(Button::kSquare));
}

/**
 * Whether the Square button was pressed since the last check.
 *
 * @return Whether the button was pressed since the last check.
 */
bool XBOXController::GetSquareButtonPressed() {
  return GetRawButtonPressed(static_cast<int>(Button::kSquare));
}

/**
 * Whether the Square button was released since the last check.
 *
 * @return Whether the button was released since the last check.
 */
bool XBOXController::GetSquareButtonReleased() {
  return GetRawButtonReleased(static_cast<int>(Button::kSquare));
}

/**
 * Read the value of the Square button on the controller.
 *
 * @return The state of the button.
 */
bool XBOXController::GetTriangleButton() const {
  return GetRawButton(static_cast<int>(Button::kTriangle));
}

/**
 * Whether the Square button was pressed since the last check.
 *
 * @return Whether the button was pressed since the last check.
 */
bool XBOXController::GetTriangleButtonPressed() {
  return GetRawButtonPressed(static_cast<int>(Button::kTriangle));
}

/**
 * Whether the Square button was released since the last check.
 *
 * @return Whether the button was released since the last check.
 */
bool XBOXController::GetTriangleButtonReleased() {
  return GetRawButtonReleased(static_cast<int>(Button::kTriangle));
}

/**
 * Read the value of the ScreenShot button on the controller.
 *
 * @param hand Side of controller whose value should be returned.
 * @return The state of the button.
 */
bool XBOXController::GetScreenShotButton() const {
  return GetRawButton(static_cast<int>(Button::kScreenShot));
}

/**
 * Whether the ScreenShot button was pressed since the last check.
 *
 * @return Whether the button was pressed since the last check.
 */
bool XBOXController::GetScreenShotButtonPressed() {
  return GetRawButtonPressed(static_cast<int>(Button::kScreenShot));
}

/**
 * Whether the ScreenShot button was released since the last check.
 *
 * @return Whether the button was released since the last check.
 */
bool XBOXController::GetScreenShotButtonReleased() {
  return GetRawButtonReleased(static_cast<int>(Button::kScreenShot));
}

/**
 * Read the value of the Options button on the controller.
 *
 * @param hand Side of controller whose value should be returned.
 * @return The state of the button.
 */
bool XBOXController::GetOptionsButton() const {
  return GetRawButton(static_cast<int>(Button::kOptions));
}

/**
 * Whether the Options button was pressed since the last check.
 *
 * @return Whether the button was pressed since the last check.
 */
bool XBOXController::GetOptionsButtonPressed() {
  return GetRawButtonPressed(static_cast<int>(Button::kOptions));
}

/**
 * Whether the Options button was released since the last check.
 *
 * @return Whether the button was released since the last check.
 */
bool XBOXController::GetOptionsButtonReleased() {
  return GetRawButtonReleased(static_cast<int>(Button::kOptions));
}

/**
 * Read the value of the PS button on the controller.
 *
 * @param hand Side of controller whose value should be returned.
 * @return The state of the button.
 */
bool XBOXController::GetPSButton() const {
  return GetRawButton(static_cast<int>(Button::kPS));
}

/**
 * Whether the PS button was pressed since the last check.
 *
 * @return Whether the button was pressed since the last check.
 */
bool XBOXController::GetPSButtonPressed() {
  return GetRawButtonPressed(static_cast<int>(Button::kPS));
}

/**
 * Whether the PS button was released since the last check.
 *
 * @return Whether the button was released since the last check.
 */
bool XBOXController::GetPSButtonReleased() {
  return GetRawButtonReleased(static_cast<int>(Button::kPS));
}
