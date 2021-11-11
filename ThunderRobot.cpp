/******************************************************************************
ThunderRobot.cpp
@wgaonar
27/10/2021

- Control of a mobile robot

Class: TB6612FNG
******************************************************************************/
#include <iostream>
#include "../../Programs/BeagleCPP/Sources/HC_SR04.h"
#include "../../Programs/BeagleCPP/Sources/KEYPAD_5BUTTONS.h"
#include "../../Programs/BeagleCPP/Sources/TB6612FNG.h"
#include "../../Programs/BeagleCPP/Sources/SERVO.h"

using namespace std;

/*===========================================================================*/
// HS_SR04 Sensors A and B
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
// Declare the Servo object
SERVO myServo(P9_14);
/*===========================================================================*/

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  double distanceToGround = distanceSensorToGround.MeasureDistanceCmWithMedian();
  cout << "Distance to ground: " << distanceToGround << "cm\n";
  DelayMilliseconds(250);

  int sonarPositions[5] = {5, 45, 95, 140, 180}; 

  for (int i = 0; i < 5; i++)
  {
    myServo.SetAngle(sonarPositions[i]);
    DelayMilliseconds(750);  // Wait 750ms for the servo to reach the position
    double distanceToFront = distanceSensorToFront.MeasureDistanceCmWithMedian();
    cout << "Distance to front: " << distanceToFront << "cm\n";
    DelayMilliseconds(250);
  }

  myServo.SetAngle(95);
  DelayMilliseconds(750);  // Wait 750ms for the servo to reach the position
  
  command = myKeyPad.ReadPushedButton();
  while (command != GO)
  {
    if (command != NOT_IDENTIFIED)
      movements.push_back(command);
    DelayMilliseconds(250);
    command = myKeyPad.ReadPushedButton();
  }

  cout << "The entered sequence of movements was: \n";
  for (int index = 0; index < movements.size(); ++index)
  {
    cout << "Movement[" << index << "] = ";
    cout  << movements.at(index) 
          << " (" << myKeyPad.GetCommandName(movements.at(index)) << ")" 
          << endl;
  }

  // Activate the module
  myTB6612FNGModule.Activate();

  message = "If you want to stop the program, enter 'y' for yes";
  cout << RainbowText(message, "Yellow") << endl;
  message = "Or enter 'w' to move forward 's' to move to backward";
  cout << RainbowText(message, "Yellow") << endl;
  message = "Or enter 'a' to move to the left or 'd' to move to the right";
  cout << RainbowText(message, "Yellow") << endl;

  int motorSpeed = 100;
  char userInput = '\0';
  while (userInput != 'y')
  {
    message = "Enter an option 'y', 'w', 's', 'a', 'd': ";
    cout << RainbowText(message, "Yellow");
    cin >> userInput;

    // Update the motors speed and move the motors in 4 directions
    switch (userInput)
    {
    case 'w':
      myTB6612FNGModule.Forward(motorSpeed);
      break;
    case 's':
      myTB6612FNGModule.Backward(motorSpeed);
      break;
    case 'a':
      myTB6612FNGModule.TurnLeft(motorSpeed);
      break;
    case 'd':
      myTB6612FNGModule.TurnRight(motorSpeed);
      break;
    default:
      break;
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