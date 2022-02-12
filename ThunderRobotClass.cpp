#include <iostream>

#include "ThunderRobotClass.h"

/*=======================HC_SR04 SENSOR SETUP================================*/
// Declaring the pins for the distance sensor to ground 
GPIO triggerPin_SensorA {P9_15};
GPIO echoPin_SensorA {P9_17};

// Declaring the pins for the distance sensor to front
GPIO triggerPin_SensorB {P9_23};
GPIO echoPin_SensorB {P9_27};
/*===========================================================================*/

/*=========================KEYPAD_5BUTTONS SETUP=============================*/
ADC VoutPin {P9_38};
LED blueLedPin {P9_11};
LED redLedPin {P9_18};
LED yellowLedPin {P9_13};
LED greenLedPin {P9_12};

COMMAND command = NOT_IDENTIFIED;
std::vector<COMMAND> movements;
/*===========================================================================*/

/*======================TB6612FNG DRIVER SETUP===============================*/
// Declare the pin to activate / deactivate the TB6612FNG module
GPIO standByPin {P8_16};

// Declaring the pins for motor A 
GPIO AIN1 {P8_12};
GPIO AIN2 {P8_14};
PWM PWMA {P8_13};

// Declare the MotorA
DCMotor MotorLeft {AIN1, AIN2, PWMA, true};

// Declaring the  pins for MotorB
GPIO BIN1 {P8_17};
GPIO BIN2 {P8_18};
PWM PWMB {P8_19};

// Declare the MotorB
DCMotor MotorRight {BIN1, BIN2, PWMB};
/*===========================================================================*/

/*=========================POSITION_SERVO SETUP==============================*/
PWM pwmServoPin {P9_14};
/*===========================================================================*/

// No-args default constructor
ThunderRobot::ThunderRobot() : 
  distanceSensorToGround {triggerPin_SensorA, echoPin_SensorA},
  distanceSensorToFront {triggerPin_SensorB, echoPin_SensorB},
  myKeyPad {VoutPin, blueLedPin, redLedPin, yellowLedPin, greenLedPin},
  myTB6612FNGModule {MotorLeft, MotorRight, standByPin},
  mySG90Servo {pwmServoPin}
{
  // Activate the module
  myTB6612FNGModule.Activate();
  DelayMilliseconds(1000);
}

/*
  Interface method to get the distance to ground
  @return double: The measured distance in cm.  
*/
double ThunderRobot::GetDistanceToGround()
{
  return distanceSensorToGround.MeasureDistanceCmWithMedian();
}

/*
  Interface method to get the distance at one angle
  @param int angle:  The desired angle (0,180) to put the servo
  @return double: The measured distance in cm.  
*/
double ThunderRobot::GetDistanceAtAngle(int angle)
{
  if (angle > 180)
    angle = 180;
  else if (angle < 0)
    angle = 0;

  mySG90Servo.SetAngle(angle);
  DelayMilliseconds(1000);
  double distance = distanceSensorToFront.MeasureDistanceCmWithMedian();
  return distance;
}

/*
  Interface method to get the distance to front
  @return double: The measured distance in cm.  
*/
double ThunderRobot::GetDistanceToFront()
{
  return GetDistanceAtAngle (90);
}

/*
  Interface method to get the distance to right
  @return double: The measured distance in cm.  
*/
double ThunderRobot::GetDistanceToRight()
{
  return GetDistanceAtAngle (0);
}

/*
  Interface method to get the distance to left
  @return double: The measured distance in cm.  
*/
double ThunderRobot::GetDistanceToLeft()
{
  return GetDistanceAtAngle (180);
}

/*
  Interface method to move the robot in one of the main 4 directions
  @param string movement: The desired direction
  @param int speed: The desired speed (0,100) with <50> as default value.
  @param int duration:  The desired duration in milliseconds with <1000> as
                        default value.
*/
void ThunderRobot::Move (std::string movement, int speed, int duration)
{
  // Check the distance to ground
  if (this->GetDistanceToGround() < 7.5)
  {
    // Move the robot according to the movement in the vector
    if (movement == "forward")
    {
      std::cout << "\nMoving the Robot to forward with a speed of: " << speed << "\% " 
                << "by: " << duration << " ms\n";
      myTB6612FNGModule.Forward(speed,duration);
    }
    else if (movement == "backward")
    {
      std::cout << "\nMoving the robot to backward with a speed of: " << speed << "\% " 
                << "by: " << duration << " ms\n";
      myTB6612FNGModule.Backward(speed,duration);
    }
    else if (movement == "left")
    {
      std::cout << "\nTurning the robot to left with a speed of: " << speed << "\% " 
                << "by: " << duration << " ms\n";
      myTB6612FNGModule.TurnLeft(speed,duration);
    }
    else if (movement == "right")
    {
      std::cout << "\nTurning the robot to right with a speed of: " << speed << "\% " 
                << "by: " << duration << " ms\n";
      myTB6612FNGModule.TurnRight(speed,duration);
    }
    else
      myTB6612FNGModule.Idle();
  }
  else
  {
    std::cout << "\nThe ThunderRobot is on the edge, moving backward\n";
    std::cout << "Moving to backward at:" << speed << "\% " 
                << "by: " << 500 << " ms\n";
    myTB6612FNGModule.Backward(speed,500);
  }
}

// Destructor
ThunderRobot::~ThunderRobot() 
{
  // Deactivate the module
  myTB6612FNGModule.Deactivate();
}