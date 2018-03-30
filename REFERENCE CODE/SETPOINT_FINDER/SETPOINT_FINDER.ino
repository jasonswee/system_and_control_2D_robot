//#include <AFMotor.h>

//AF_DCMotor motorLeft(1, MOTOR12_1KHZ);
//AF_DCMotor motorRight(4, MOTOR12_1KHZ);

const int sensor[5] = {A1, A2, A3, A4, A5}; // Setting sensor array to analog pins

int sensorReadings[5] = {0, 0, 0, 0, 0}; // For storing sensor readings
long sensorWeighted;
long sensorSum;

int errorValue = 0;



void setup() {
for (int i = 0; i < 5; i++){    
    pinMode(sensor[i], INPUT);
}
    Serial.begin(9600);
}

void loop() {
  sensorWeighted = 0L;
  sensorSum = 0L;
  long Position = 0L;
  
  for (int i = 0; i < 5; i++){
    sensorReadings[i] = analogRead(sensor[i]);
    sensorWeighted += sensorReadings[i] * (i+1) * 1000L;  // Calculating the weighted version of the sensor readings
    sensorSum += sensorReadings[i]; // Calculating sum of sensor readings 
  }  
  Position = sensorWeighted/sensorSum;
/*
for(int i = 0; i<5;i++){
  Serial.print("Sensor ");
  Serial.print(i+1);
  Serial.println(": ");
  Serial.println(sensorReadings[i]);
}
*/

  Serial.println(Position);
  delay(100);

}
