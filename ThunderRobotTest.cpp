/******************************************************************************
ThunderRobot.cpp
@wgaonar
12/02/2022

- Control of a mobile robot

******************************************************************************/
#include <iostream>
#include "ThunderRobotClass.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  ThunderRobot myRobot;

  cout << "\nMeasuring the distance to ground\n";
  double distanceToGround = myRobot.GetDistanceToGround();
  cout << "Distance to ground: " << distanceToGround << "cm\n";
  DelayMilliseconds(250);

  cout << "\nMeasuring the distance to right\n";
  double distanceToRight= myRobot.GetDistanceToRight();
  cout << "Distance to right: " << distanceToRight << "cm\n";
  DelayMilliseconds(250);

  cout << "\nMeasuring the distance to left\n";
  double distanceToLeft= myRobot.GetDistanceToLeft();
  cout << "Distance to left: " << distanceToLeft << "cm\n";
  DelayMilliseconds(250);
  
  cout << "\nMeasuring the distance to front\n";
  double distanceToFront= myRobot.GetDistanceToFront();
  cout << "Distance to front: " << distanceToFront << "cm\n";
  DelayMilliseconds(250);

  // Test the robot movements
  cout << "\nMoving the ThunderRobot...\n";

  int motorSpeed {100};
  myRobot.Move("forward", motorSpeed, 1000);
  myRobot.Move("backward", motorSpeed, 1000);
  myRobot.Move("left", motorSpeed, 1000);
  myRobot.Move("right", motorSpeed, 1000);

  myRobot.Turn90Degrees("left");
  myRobot.Turn90Degrees("right");

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}