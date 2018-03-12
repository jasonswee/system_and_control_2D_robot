#include <AFMotor.h>
 
AF_DCMotor motorLeft(1, MOTOR12_1KHZ);
AF_DCMotor motorRight(4, MOTOR12_1KHZ);

const int sensor[5] = {A0, A1, A2, A3, A4}; // Setting sensor array to analog pins
const float Kp = 0.8; //CHANGE THESE
const float Ki = 0.4;
const float Kd = 0.3;
const int setPoint = 3000; // YOU SHOULD CHANGE THIS (This is what the robot will refer to as 'correct') Find position at set point and put the value in.
const int maxSpeed = 200; //YOU CAN CHANGE THIS

int leftSpeed = 0;
int rightSpeed = 0;

int sensorReadings[5] = {0, 0, 0, 0, 0}; // For storing sensor readings
long sensorWeighted;
long sensorSum;

int correctionValue = 0;
double lastProportional = 0.0;

void readSensors() {
  sensorWeighted = 0;
  sensorSum = 0;
  for (int i = 0; i < 5; i++){
    sensorReadings[i] = analogRead(sensor[i]);
    sensorWeighted += sensorReadings[i] * (i + 1) * 1000L;  // Calculating the weighted version of the sensor readings
    sensorSum += sensorReadings[i]; // Calculating sum of sensor readings 
  }
}

void pidCalc() {
  long Position = sensorWeighted / sensorSum;
  long Proportional = Position - setPoint; // Finds difference from setPoint
  long Integral = Integral + Proportional; // Sums differences iteratively
  long Derivative = Proportional - lastProportional; // Finds rate of change of difference
  lastProportional = Proportional; // Saves difference state for referencing derivative

  correctionValue = int(Proportional * Kp + Integral * Ki + Derivative * Kd); // Applies PID weights
}

void turnCalc(){  
// Restrict correctionValue to [- maxSpeed, maxSpeed]
  if (correctionValue < -maxSpeed || correctionValue > maxSpeed) { 
    if (correctionValue < -maxSpeed) {
      correctionValue= -maxSpeed;
    }
    if (correctionValue > maxSpeed) {
      correctionValue = maxSpeed;
    }      
  }
 
// Calculate turn values
  if (correctionValue < 0) {
    rightSpeed = maxSpeed + correctionValue;
    leftSpeed = maxSpeed;
    }
    
    else {
    rightSpeed = maxSpeed;
    leftSpeed = maxSpeed - correctionValue;
    }
}

void setMotors() {
  motorLeft.setSpeed(leftSpeed);
  motorRight.setSpeed(rightSpeed);
}

void setup()
{
for (int i = 0; i < 5; i++){    
    pinMode(sensor[i], INPUT);
}
    Serial.begin(9600);
}
 
void loop()
{
  readSensors();  //Reads sensor values and computes sensor sum and weighted average
  pidCalc();      //Calculates position[set point] and computes Kp, Ki and Kd
  turnCalc();     //Computes the error to be corrected
  setMotors();  //Sends PWM signals to the motors
  
  motorRight.run(FORWARD);
  motorLeft.run(FORWARD);
 
  delay(10);


  Serial.print("L: ");  
  Serial.print(leftSpeed);
  Serial.print("    ");
  Serial.print("R: ");
  Serial.println(rightSpeed);

  Serial.println(correctionValue);
/*
  for (int i = 0; i <5; i++) {
      Serial.print("SNSR ");
      Serial.print(i);
      Serial.print(":");
      Serial.println(int(sensor[i]));

  }
  */
  Serial.println("");
}
