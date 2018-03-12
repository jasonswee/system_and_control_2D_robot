#include <AFMotor.h>

AF_DCMotor motorLeft(1, MOTOR12_1KHZ);
AF_DCMotor motorRight(4, MOTOR12_1KHZ);

const int sensor[5] = {A0, A1, A2, A3, A4}; // Setting sensor array to analog pins

int sensorReadings[5] = {0, 0, 0, 0, 0}; // For storing sensor readings

void setup() {
for (int i = 0; i < 5; i++){    
    pinMode(sensor[i], INPUT);
}
    Serial.begin(9600);
}

void loop() {

for(int i = 0; i<5;i++){
  Serial.print("Sensor ");
  Serial.print(i+1);
  Serial.println(": ");
  Serial.println(sensorReadings[i]);
}

  delay(100);

}
