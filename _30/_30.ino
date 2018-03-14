#include "Mcontrol.h"

Mcontrol mcontrol();

int adc_key_val[5] ={30, 150, 360, 535, 760 };
int NUM_KEYS = 5;
int adc_key_in;
int key=-1;
int oldkey=-1;

//Standard PWM DC control
//int E1 = 5;     //M1 Speed Control
//int E2 = 6;     //M2 Speed Control
//int M1 = 4;    //M1 Direction Control
//int M2 = 7;    //M1 Direction Control

///For previous Romeo, please use these pins.
//int E1 = 6;     //M1 Speed Control
//int E2 = 9;     //M2 Speed Control
//int M1 = 7;    //M1 Direction Control
//int M2 = 8;    //M1 Direction Control

const float Kp = 0.8; //CHANGE THESE
const float Ki = 0.4;
const float Kd = 0.3;

const int setPoint = 3000;

void stop(void)                    //Stop
{
  digitalWrite(E1,LOW);   
  digitalWrite(E2,LOW);      
}   
void advance(char a,char b)          //Move forward
{
  analogWrite (E1,a);      //PWM Speed Control
  digitalWrite(M1,HIGH);    
  analogWrite (E2,b);    
  digitalWrite(M2,HIGH);
}  
void back_off(char a,char b)          //Move backward
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);   
  analogWrite (E2,b);    
  digitalWrite(M2,LOW);
}
void turn_L(char a,char b)             //Turn Left
{
  analogWrite (E1,a);
  digitalWrite(M2,LOW);    
  analogWrite (E2,b);    
  digitalWrite(M1,HIGH);
}
void turn_R(char a,char b)             //Turn Right
{
  analogWrite (E1,a);
  digitalWrite(M2,HIGH);    
  analogWrite (E2,b);    
  digitalWrite(M1,LOW);
}

// Convert ADC value to key number
int get_key(unsigned int input)
{   
  int k;
  for (k = 0; k < NUM_KEYS; k++)
  {
    if (input < adc_key_val[k])
    {  
      return k;  
    }
  }
  if (k >= NUM_KEYS)
    k = -1;     // No valid key pressed
  return k;
}
void keyboard_control(void)
{
  if(Serial.available()){
    char val = Serial.read();
    if(val != -1)
    {
      switch(val)
      {
      case 'w'://Move Forward
        advance (150,150);   //move forward in max speed
        break;
      case 's'://Move Backward
        back_off (150,150);   //move back in max speed
        break;
      case 'a'://Turn Left
        turn_L (150,150);
        break;       
      case 'd'://Turn Right
        turn_R (150,150);
        break;
      case 'z':
        Serial.println("Hello");
        break;
      case 'x':
        stop();
        break;
      }
    }
    else stop();  
  }
}
void onboard_button_control(void)
{
  adc_key_in = analogRead(0);    // read the value from the sensor  
  digitalWrite(13, HIGH);
  
  /* get the key */
  key = get_key(adc_key_in);    // convert into key press
  if (key != oldkey) {   // if keypress is detected
    
    delay(50);      // wait for debounce time
    adc_key_in = analogRead(0);    // read the value from the sensor  
    key = get_key(adc_key_in);    // convert into key press
      if (key >=0){
        Serial.println(adc_key_in, DEC);
        Serial.println(key, DEC);
        switch(key){
          case 0:
            advance(150,150);
            break;
          case 1:
            turn_L(150,150);
            break;
          case 2:
            back_off(150,150);
            break;
          case 3:
            turn_R(150,150);
            break;
          case 4:
            stop();
            break;
            
        }
//        delay(1000);
//        stop1();

      }
      oldkey=-1;
    }
  digitalWrite(13, LOW);
}
void setup(void) 
{
  pinMode(13, OUTPUT);  //we'll use the debug LED to output a heartbeat
  int i;
  for(i=4;i<=7;i++)
    pinMode(i, OUTPUT);
  Serial.begin(9600);      //Set Baud Rate
  Serial.println("Run keyboard control");
} 
void loop(void) 
{
  //keyboard_control();
  //onboard_button_control();
  //mcontrol.advance(12,123);
	
  
}
