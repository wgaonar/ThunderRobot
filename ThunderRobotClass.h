#ifndef _THUNDERROBOTCLASS_H
#define _THUNDERROBOTCLASS_H

#include "../../Programs/BeagleCPP/Sources/HC_SR04.h"
#include "../../Programs/BeagleCPP/Sources/KEYPAD_5BUTTONS.h"
#include "../../Programs/BeagleCPP/Sources/TB6612FNG.h"
#include "../../Programs/BeagleCPP/Sources/POSITION_SERVO.h"

class ThunderRobot
{
private:
  // Sensors
  HC_SR04 distanceSensorToGround;
  HC_SR04 distanceSensorToFront;
  KEYPAD_5BUTTONS myKeyPad;

  // Actuators
  TB6612FNG myTB6612FNGModule;
  POSITION_SERVO mySG90Servo;

public:
  // No-args default constructor
  ThunderRobot();

  // Interface method to get the distance to ground
  double virtual GetDistanceToGround();

  // Interface method to get the distance at angle
  double virtual GetDistanceAtAngle(int angle);

  // Interface method to get the distance to front
  double virtual GetDistanceToFront();

  // Interface method to get the distance to right
  double virtual GetDistanceToRight();

  // Interface method to get the distance to left
  double virtual GetDistanceToLeft();

  // Interface method to get the pressed Button from the Keypad
  COMMAND virtual GetKeyPadButton();

  // Interface method to move the robot to forward / backward
  virtual void Move (std::string movement, int speed = 50, int duration = 1000);

  // Interface method to move the robot 10cm to forward / backward
  virtual void Move10cm (std::string movement);

  // Interface method to move the robot 5cm to forward / backward
  virtual void Move5cm (std::string movement);

  // Interface method to turn the robot to the left / right
  virtual void Turn (std::string movement, int speed = 50, int duration = 1000);

  // Interface method to turn 90 degrees the robot
  virtual void Turn90Degrees(std::string direction);

  // Interface method to turn 45 degrees the robot
  virtual void Turn45Degrees(std::string direction);

  // Interface method to turn 30 degrees the robot
  virtual void Turn30Degrees(std::string direction);

  // Destructor
  ~ThunderRobot();
};

#endif // _THUNDERROBOTCLASS_H