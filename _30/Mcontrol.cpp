/*
  Mcontrol.cpp - Library for Motor Control code.
  Created by Jason Swee, March 12, 2018.
*/
//#include "Arduino.h"
#include "Mcontrol.h"

Mcontrol::Mcontrol()//float left, float right)
{
	//_left = left;
	//_right = right;

}
void Mcontrol::stop()                    //Stop
{
  //digitalWrite(E1,LOW);
  //igitalWrite(E2,LOW);
}
void Mcontrol::advance(float a,float b)          //Move forward
{
  //analogWrite(E1,a);      //PWM Speed Control
  //digitalWrite(M1,HIGH);
  //analogWrite(E2,b);
  //digitalWrite(M2,HIGH);
}
void Mcontrol::back_off(char a,char b)          //Move backward
{
  //analogWrite (E1,a);
  //digitalWrite(M1,LOW);
  //analogWrite (E2,b);
  //digitalWrite(M2,LOW);
}
void Mcontrol::turn_L(char a,char b)             //Turn Left
{
  //analogWrite (E1,a);
  //digitalWrite(M2,LOW);
  //analogWrite (E2,b);
  //digitalWrite(M1,HIGH);
}
void Mcontrol::turn_R(char a,char b)             //Turn Right
{
  //analogWrite (E1,a);
  //digitalWrite(M2,HIGH);
  //analogWrite (E2,b);
  //digitalWrite(M1,LOW);
}




