/******************************************************************************
ThunderRobot.cpp
@wgaonar
27/10/2021

- Control of a mobile robot

******************************************************************************/
#include <iostream>
#include "../../Programs/BeagleCPP/Sources/HC_SR04.h"
#include "../../Programs/BeagleCPP/Sources/KEYPAD_5BUTTONS.h"
#include "../../Programs/BeagleCPP/Sources/TB6612FNG.h"
#include "../../Programs/BeagleCPP/Sources/POSITION_SERVO.h"

using namespace std;

/*===========================================================================*/
// HC_SR04 Sensors A and B
// Declaring the pins for Sensor A 
GPIO triggerPin_SensorA(P9_15);
GPIO echoPin_SensorA(P9_17);

// Declaring object for HC_SR04 A
HC_SR04 distanceSensorToGround (triggerPin_SensorA, echoPin_SensorA);

// Declaring the pins for sensor B
GPIO triggerPin_SensorB(P9_23);
GPIO echoPin_SensorB(P9_27);

// Declaring object for HC_SR04 B
HC_SR04 distanceSensorToFront (triggerPin_SensorB, echoPin_SensorB);
/*===========================================================================*/

/*===========================================================================*/
// KEYPAD_5BUTTONS
// Declaring the pins
ADC VoutPin(P9_38);
LED blueLedPin(P9_11);
LED redLedPin(P9_18);
LED yellowLedPin(P9_13);
LED greenLedPin(P9_12);

// Global KEYPAD_5BUTTONS object instantiation
KEYPAD_5BUTTONS myKeyPad (VoutPin, blueLedPin, redLedPin, yellowLedPin, greenLedPin);

// Global Variables
COMMAND command = NOT_IDENTIFIED;
vector<COMMAND> movements;
/*===========================================================================*/

/*===========================================================================*/
// TB6612FNG Driver
// Declare the pin to activate / deactivate the TB6612FNG module
GPIO standByPin(P8_16);

// Declaring the pins for motor A 
GPIO AIN1 (P8_12);
GPIO AIN2 (P8_14);
PWM PWMA (P8_13);

// Declare the MotorA
DCMotor MotorLeft (AIN1, AIN2, PWMA, true);

// Declaring the  pins for MotorB
GPIO BIN1 (P8_17);
GPIO BIN2 (P8_18);
PWM PWMB (P8_19);

// Declare the MotorB
DCMotor MotorRight (BIN1, BIN2, PWMB);

// Declare the TB6612FNG Module
TB6612FNG myTB6612FNGModule (MotorLeft, MotorRight, standByPin);
/*===========================================================================*/

/*===========================================================================*/
// Servomotor SG90
// Declare the POSITION_SERVO object
POSITION_SERVO myServo(P9_14);
/*===========================================================================*/

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  cout << "\nMeasuring the distance to ground\n";
  double distanceToGround {distanceSensorToGround.MeasureDistanceCmWithMedian()};
  cout << "Distance to ground: " << distanceToGround << "cm\n";
  DelayMilliseconds(250);

  cout << "\nMaking a sonar sweep to measure the distance to surroundings\n";
  int sonarPositions[5] {5, 45, 95, 140, 180}; 
  for (int i = 0; i < 5; i++)
  {
    myServo.SetAngle(sonarPositions[i]);
    // Wait 1000ms for the servo to reach the position
    DelayMilliseconds(1000);  
    double distanceToFront = distanceSensorToFront.MeasureDistanceCmWithMedian();
    cout << "Distance to front: " << distanceToFront << "cm\n";
  }

  myServo.SetAngle(95);
  // Wait 1000ms for the servo to reach the center position
  DelayMilliseconds(1000);


  cout  << "\nPlease, enter the desired movement sequence with the keypad"
        << "White bottom to execute them\n";
  command = myKeyPad.ReadPushedButton();
  while (command != GO)
  {
    if (command != NOT_IDENTIFIED)
      movements.push_back(command);
    DelayMilliseconds(250);
    command = myKeyPad.ReadPushedButton();
  }

  cout << "\nThe entered sequence of movements was: \n";
  for (int index = 0; index < movements.size(); ++index)
  {
    cout << "Movement[" << index << "] = ";
    cout  << movements.at(index) 
          << " (" << myKeyPad.GetCommandName(movements.at(index)) << ")" 
          << endl;
  }

  cout << "\nMoving the ThunderRobot...\n";
  // Activate the module
  myTB6612FNGModule.Activate();

  int motorSpeed = 100;
  for (auto movement : movements)
  {
    // Check the distance to ground
    distanceToGround = distanceSensorToGround.MeasureDistanceCmWithMedian();
    if (distanceToGround < 7.5)
    {
      // Move the robot according to the movement in the vector
      switch (movement)
      {
      case FORWARD:
        myTB6612FNGModule.Forward(motorSpeed,1000);
        break;
      case BACKWARD:
        myTB6612FNGModule.Backward(motorSpeed,1000);
        break;
      case LEFT:
        myTB6612FNGModule.TurnLeft(motorSpeed,1000);
        break;
      case RIGHT:
        myTB6612FNGModule.TurnRight(motorSpeed,1000);
        break;
      default:
        break;
      }
    }
    else
    {
      cout << "The ThunderRobot is on the edge, moving backward\n";
      myTB6612FNGModule.Backward(motorSpeed,250);
    }
  }

  // Brake the motors
  cout << "Breaking the motors...\n";
  myTB6612FNGModule.Brake();

  // Deactivate the module
  myTB6612FNGModule.Deactivate();

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}