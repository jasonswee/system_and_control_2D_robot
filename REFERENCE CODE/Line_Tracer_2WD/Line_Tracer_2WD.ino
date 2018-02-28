#include <AFMotor.h>
 
AF_DCMotor motorLeft(1, MOTOR12_1KHZ);
AF_DCMotor motorRight(4, MOTOR12_1KHZ);
 
const int rightThresh = 500;
const int leftThresh = 500;
 
const int rightPin = A2;
const int leftPin = A4;
 
void setup()
{
    pinMode(rightPin, INPUT);
    pinMode(leftPin, INPUT);
    Serial.begin(9600);
}
 
void loop()
{
    int rightValue = analogRead(rightPin);
    int leftValue = analogRead(leftPin);
 
    if (rightValue >= rightThresh) {
        if (leftValue >= leftThresh) {
            motorLeft.setSpeed(150);
            motorRight.setSpeed(150);
        }
 
        else {
            Serial.println("left");
            motorLeft.setSpeed(0);
            motorRight.setSpeed(150);
        }
 
    }
 
    else {
        if (leftValue >= leftThresh) {
            motorLeft.setSpeed(150);
            motorRight.setSpeed(0);
        }
 
        else {
            motorLeft.setSpeed(0);
            motorRight.setSpeed(0);
 
        }
 
    }
    motorRight.run(FORWARD);
    motorLeft.run(FORWARD);
    delay(10);
    Serial.print(leftValue);
    Serial.print("    ");
    Serial.println(rightValue);
 
}
