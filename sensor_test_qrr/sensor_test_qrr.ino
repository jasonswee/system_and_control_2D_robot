const int a_no = 5; //Analog sensor count
//const int d_no = 3; //Digital sensor count

int s_reads[5] = {0, 0, 0, 0, 0}; // For storing sensor readings

const int a_pins[a_no] = {A1,A2,A3,A4,A5}; // Setting sensor array to analog pins, including LDR sensor
//const int d_pins[d_no] = {0,1,2}; // Setting sensor array to digital pins

QTRSensorsRC qtrrc((unsigned char[]) {
  A5, A4, A3, A3, A1
} , NUM_SENSORS, TIMEOUT, EMITTER_PIN); // sensor connected through analog pins A0 - A4 i.e. digital pins 14-19 in uno


void setup()
{
	for (int i = 0; i < a_no; i++)
	{
		pinMode(a_pins[i], INPUT);
	}
	/*for (int i = 0; i < d_no; i++)
	{
		pinMode(d_pins[i], INPUT);
	}*/
 for (int i = 0; i < 100; i++) // calibrate for sometime by sliding the sensors across the line, or you may use auto-calibration instead

    /* comment this part out for automatic calibration
      if ( i  < 25 || i >= 75 ) // turn to the left and right to expose the sensors to the brightest and darkest readings that may be encountered
       turn_right();
      else
       turn_left(); */
    qtrrc.calibrate();
  delay(20);
   Serial.begin(9600);
  for (int i = 0; i < NUM_SENSORS; i++)
  {
  Serial.print(qtrrc.calibratedMinimumOn[i]);
  Serial.print(' ');
  }
  Serial.println();

  for (int i = 0; i < NUM_SENSORS; i++)
  {
  Serial.print(qtrrc.calibratedMaximumOn[i]);
  Serial.print(' ');
  }
  Serial.println();
  Serial.println();
}

void loop() {

for(int i = 1; i<=a_no;i++){
  s_reads[i] = analogRead(a_pins[i]);
  Serial.print("Analog Sensor ");
  Serial.print(i);
  Serial.print(": ");
  Serial.print(s_reads[i]);
  Serial.print("  ");
}
Serial.println();
/*
for(int i = 0; i<d_no;i++){
  s_reads[i] = digitalRead(d_pins[i]);
  Serial.print("Digital Sensor ");
  Serial.print(i);
  Serial.println(": ");
  Serial.println(s_reads[i]);
}*/
  delay(100);
}
