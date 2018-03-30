/*
  Mcontrol.h - Library for Motor control code.
  Created by Jason Swee, March 12, 2018.
  Released into the public domain.
*/
#ifndef Mcontrol_h
#define Mcontrol_h

#define rightMaxSpeed 200 // max speed of the robot
#define leftMaxSpeed 200 // max speed of the robot

//Standard PWM DC control
#define E1 5     //M1 Speed Control
#define E2 6     //M2 Speed Control
#define M1 4    //M1 Direction Control
#define M2 7    //M1 Direction Control

//#include "Arduino.h"

class Mcontrol
{
  public:
	Mcontrol();//float left, float right);
    void advance(float left,float right);
    void stop();                    //Stop
    void back_off(char a,char b);          //Move backward
    void turn_L(char a,char b);             //Turn Left
    void turn_R(char a,char b);
  private:
    //float _left, _right;
};


#endif
