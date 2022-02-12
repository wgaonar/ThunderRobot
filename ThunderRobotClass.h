#ifndef _THUNDERROBOTCLASS_H
#define _THUNDERROBOTCLASS_H

#include "../../Programs/BeagleCPP/Sources/HC_SR04.h"
#include "../../Programs/BeagleCPP/Sources/KEYPAD_5BUTTONS.h"
#include "../../Programs/BeagleCPP/Sources/TB6612FNG.h"
#include "../../Programs/BeagleCPP/Sources/POSITION_SERVO.h"
// #include "Configuration.h"

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

  // Interface method to do a sweep to get distance at different angles
   
  // Interface method to move the robot to forward
  virtual void Move (std::string movement, int speed = 50, int duration = 1000);

  // Destructor
  ~ThunderRobot();
};

#endif // _THUNDERROBOTCLASS_H