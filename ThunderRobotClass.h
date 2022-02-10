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
  POSITION_SERVO myServo;

public:
  // No-args default constructor
  ThunderRobot();

  // Interface method to get the distance to front
  double virtual GetDistanceToFront();
};

#endif // _THUNDERROBOTCLASS_H