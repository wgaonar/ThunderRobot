/******************************************************************************
ThunderRobot-CopaVino.cpp
@wgaonar
08/03/2022

- Control of a mobile robot to make a trace of "glass of wine" shape

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

  /*
  cout << "\nMeasuring the distance to front\n";
  double distanceToFront= myRobot.GetDistanceToFront();
  cout << "Distance to front: " << distanceToFront << "cm\n";
  DelayMilliseconds(250);

  cout << "\nMeasuring the distance to right\n";
  double distanceToRight= myRobot.GetDistanceToRight();
  cout << "Distance to right: " << distanceToRight << "cm\n";
  DelayMilliseconds(250);

  cout << "\nMeasuring the distance to left\n";
  double distanceToLeft= myRobot.GetDistanceToLeft();
  cout << "Distance to left: " << distanceToLeft << "cm\n";
  DelayMilliseconds(250);
  */

  // Test the robot movements
  cout << "\nMoving the ThunderRobot...\n";

  /*
  myRobot.Move("forward", motorSpeed, 1000);
  myRobot.Move("backward", motorSpeed, 1000);
  
  myRobot.Turn("left", motorSpeed, 1000);
  myRobot.Turn("right", motorSpeed, 1000);
  */

  /*
  for (size_t i = 0; i < 4; i++)
  {
    myRobot.Move10cm("forward");
    myRobot.Move10cm("backward");
  }
  */

  for (size_t i = 0; i < 15; i++)
    myRobot.Move10cm("forward");

  myRobot.Turn90Degrees("left");

  for (size_t i = 0; i < 5; i++)
    myRobot.Move10cm("forward");

  myRobot.Turn90Degrees("left");

  for (size_t i = 0; i < 5; i++)
    myRobot.Move10cm("forward");

  myRobot.Turn90Degrees("right");
  
  for (size_t i = 0; i < 5; i++)
    myRobot.Move10cm("forward");

  myRobot.Turn45Degrees("right");

  for (size_t i = 0; i < 7; i++)
    myRobot.Move10cm("forward");

  myRobot.Turn45Degrees("left");

  for (size_t i = 0; i < 10; i++)
    myRobot.Move10cm("forward");
  
  myRobot.Turn90Degrees("left");

  for (size_t i = 0; i < 15; i++)
    myRobot.Move10cm("forward");

  myRobot.Turn90Degrees("left");
  
  for (size_t i = 0; i < 10; i++)
    myRobot.Move10cm("forward");

  myRobot.Turn45Degrees("left");

  for (size_t i = 0; i < 7; i++)
    myRobot.Move10cm("forward");

  myRobot.Turn45Degrees("right");

  for (size_t i = 0; i < 5; i++)
    myRobot.Move10cm("forward");

  myRobot.Turn90Degrees("right");

  for (size_t i = 0; i < 5; i++)
    myRobot.Move10cm("forward");

  myRobot.Turn90Degrees("left");

  for (size_t i = 0; i < 5; i++)
    myRobot.Move10cm("forward");

  message = "Main program finishes here Bye Bye...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}