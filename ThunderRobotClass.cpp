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

// Declare the TB6612FNG Module
TB6612FNG myTB6612FNGModule (MotorLeft, MotorRight, standByPin);
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
  this->myTB6612FNGModule.Activate();
  DelayMilliseconds(1000);
}

/*
  Interface method to get the distance to ground
  @return double: The measured distance in cm.  
*/
double ThunderRobot::GetDistanceToGround()
{
  return this->distanceSensorToGround.MeasureDistanceCmWithMedian();
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

  this->mySG90Servo.SetAngle(angle);
  DelayMilliseconds(1000);
  double distance = this->distanceSensorToFront.MeasureDistanceCmWithMedian();
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
  Interface method to get the pressed Button from the Keypad
  @return COMMAND: The pressed button.  
*/
COMMAND ThunderRobot::GetKeyPadButton()
{
  return this->myKeyPad.ReadPushedButton();
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
      std::cout << "\nMoving the Robot to forward with a speed of: " 
                << speed << "\% " << "by: " << duration << " ms\n";
      this->myTB6612FNGModule.Forward(speed, duration);
    }
    else if (movement == "backward")
    {
      std::cout << "\nMoving the robot to backward with a speed of: " 
                << speed << "\% " << "by: " << duration << " ms\n";
      this->myTB6612FNGModule.Backward(speed, duration);
    }
    else if (movement == "left")
    {
      std::cout << "\nTurning the robot to left with a speed of: " 
                << speed << "\% " << "by: " << duration << " ms\n";
      this->myTB6612FNGModule.TurnLeft(speed,duration);
    }
    else if (movement == "right")
    {
      std::cout << "\nTurning the robot to right with a speed of: " 
                << speed << "\% " << "by: " << duration << " ms\n";
      this->myTB6612FNGModule.TurnRight(speed,duration);
    }
    else
      this->myTB6612FNGModule.Idle();
  }
  else
  {
    std::cout << "\nThe ThunderRobot is on the edge, moving backward\n";
    this->myTB6612FNGModule.Backward(speed,500);
  }
}

/*
  Interface method to turn 90° degrees the robot to the left or right
  @param string direction: The desired turn direction
*/
void ThunderRobot::Turn90Degrees( std::string direction)
{
  if (direction == "left")
  {
    std::cout << "\nTurning the robot 90° to left\n";
    this->myTB6612FNGModule.TurnLeft(100,3200);
  }
  else if (direction == "right")
  {
    std::cout << "\nTurning the robot 90° to right\n";
    this->myTB6612FNGModule.TurnRight(100,3000);
  }
  else
  {
    this->myTB6612FNGModule.Idle();
  }
}

// Destructor
ThunderRobot::~ThunderRobot() 
{
  // Deactivate the module
  this->myTB6612FNGModule.Deactivate();
}