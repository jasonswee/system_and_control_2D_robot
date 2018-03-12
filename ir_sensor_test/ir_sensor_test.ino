#define IR0 A0  //Left most sensor
#define IR1 A1
#define IR2 A2  //Centre
#define IR3 A3
#define IR4 A4  //Right most sensor

const int sensor[5] = {IR0, IR1, IR2, IR3, IR4}; // Setting sensor array to analog pins

int sensorReadings[5] = {0, 0, 0, 0, 0}; // For storing sensor readings

void setup()
{
	for (int i = 0; i < 5; i++)
	{
		pinMode(sensor[i], INPUT);
	}
    Serial.begin(9600);
}

void loop() {

for(int i = 0; i<5;i++){
  Serial.print("Sensor ");
  Serial.print(i);
  Serial.println(": ");
  Serial.println(sensorReadings[i]);
}
  delay(100);
}
