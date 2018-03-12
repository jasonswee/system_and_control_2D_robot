const int a_no = 3; //Analog sensor count
const int d_no = 3; //Digital sensor count

int s_reads[6] = {0, 0, 0, 0, 0, 0}; // For storing sensor readings

const int a_pins[a_no] = {A0,A1,A2}; // Setting sensor array to analog pins, including LDR sensor
const int d_pins[d_no] = {0,1,2}; // Setting sensor array to digital pins



void setup()
{
	for (int i = 0; i < a_no; i++)
	{
		pinMode(a_pins[i], INPUT);
	}
	for (int i = 0; i < d_no; i++)
	{
		pinMode(d_pins[i], INPUT);
	}
    Serial.begin(9600);
}

void loop() {

for(int i = 0; i<a_no;i++){
  s_reads[i] = analogRead(a_pins[i]);
  Serial.print("Analog Sensor ");
  Serial.print(i);
  Serial.println(": ");
  Serial.println(s_reads[i]);
}
for(int i = 0; i<d_no;i++){
  s_reads[i] = digitalRead(d_pins[i]);
  Serial.print("Digital Sensor ");
  Serial.print(i);
  Serial.println(": ");
  Serial.println(s_reads[i]);
}
  delay(100);
}
