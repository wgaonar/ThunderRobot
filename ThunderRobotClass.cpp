#include <iostream>

#include "ThunderRobotClass.h"

// No-args default constructor
ThunderRobot::ThunderRobot()
{
  // Declaring the pins for the Sensor  
  GPIO triggerPin_SensorA (P9_15);
  GPIO echoPin_SensorA (P9_17);
  distanceSensorToGround (triggerPin_SensorA, echoPin_SensorA);
}