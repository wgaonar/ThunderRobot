/******************************************************************************
ThunderRobot-RemoteControl.cpp
@wgaonar
12/02/2022

- Control the Thunder Robot with the Keyboard

******************************************************************************/
#include <iostream>
#include "ThunderRobotClass.h"

using namespace std;

int main()
{
  string message = "Main program starting here...";
  cout << RainbowText(message,"Blue", "White", "Bold") << endl;

  ThunderRobot myRobot;

  cout  << "\nMove the Robot with the keystrokes: 'w', 's', 'a', 'd' "
        << "and 'y' for exit\n";
  
  double distanceToFront{0};
  double distanceToGround {0};

  char userInput = '\0';
  while (userInput != 'y')
  {
    cout << "Waiting for the user keystroke: ";
    cin >> userInput;

    switch (userInput)
    {
      case 'w':
        myRobot.Move10cm("forward");
        break;

      case 's':
        myRobot.Move10cm("backward");
        break;

      case 'd':
        myRobot.Turn90Degrees("right");
        break;

      case 'a':
        myRobot.Turn90Degrees("left");
        break;

      case 'p':
        distanceToFront = myRobot.GetDistanceToFront();
        cout << "Distance to front: " << distanceToFront << "cm\n";
        DelayMilliseconds(250);
        break;
      
      case 'o':
        distanceToGround = myRobot.GetDistanceToGround();
        cout << "Distance to ground: " << distanceToGround << "cm\n";
        DelayMilliseconds(250);
        break;
      
      default:
        break;
    }
  }

  message = "Main program finishes here...";
  cout << RainbowText(message,"Blue", "White","Bold") << endl;

  return 0;
}