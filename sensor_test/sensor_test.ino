const int a_no = 5; //Analog sensor count

int s_reads[5] = {0, 0, 0, 0, 0}; // For storing sensor readings

const int a_pins[a_no] = {A1,A2,A3,A4,A5}; // Setting sensor array to analog pins, including LDR sensor

int single_pin = A5;
int single_read = 0;

void setup()
{
	for (int i = 0; i < a_no; i++)
	{
		pinMode(a_pins[i], INPUT);
	}
    Serial.begin(9600);
}

void loop() {
  single_read = analogRead(single_pin);
  Serial.print("A_Sensor ");
  Serial.print(single_read);
  Serial.println();
  single_read = map(single_read, 300, 1023, 0, 1000);
  Serial.print("Calibrater_Sensor ");
  Serial.print(single_read);

/*
for(int i = 0; i<=a_no;i++){
  s_reads[i] = analogRead(a_pins[i]);
  Serial.print("A_Sensor ");
  Serial.print(i);
  Serial.print(": ");
  Serial.print(s_reads[i]);
  Serial.print("  ");
}*/
Serial.println();
  delay(100);
}
