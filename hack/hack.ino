const int sensor[5] = {A1, A2, A3, A4, A5}; // Setting sensor array to analog pins
const float Kp = 0.3;//0.8; //CHANGE THESE
const float Ki = 0;//0.4;
const float Kd = 0.5;//0.3;
const int setPoint = 2865; // YOU SHOULD CHANGE THIS (This is what the robot will refer to as 'correct') Find position at set point and put the value in.
const int maxSpeed = 120; //YOU CAN CHANGE THIS
const int ldr_pin = A0;
int E1 = 6;     //M1 Speed Control
int E2 = 5;     //M2 Speed Control
int M1 = 4;    //M1 Direction Control
int M2 = 7;    //M1 Direction Control

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
  for(int i = 0; i <5;i++){//for (int i = 0; i < 5; i++){
    sensorReadings[i] = map(analogRead(sensor[i]), 0, 1023, 0, 1000);
    sensorWeighted += sensorReadings[i] * (i + 1) * 1000L;  // Calculating the weighted version of the sensor readings
    sensorSum += sensorReadings[i]; // Calculating sum of sensor readings 
  }
}

void pidCalc() {
  long Position = sensorWeighted / sensorSum;
  Serial.print("Postion: ");
  Serial.println(Position);
  long Proportional = Position - setPoint; // Finds difference from setPoint
  long Integral = Integral + Proportional; // Sums differences iteratively
  long Derivative = Proportional - lastProportional; // Finds rate of change of difference
  lastProportional = Proportional; // Saves difference state for referencing derivative

  correctionValue = int(Proportional * Kp + Integral * Ki + Derivative * Kd); // Applies PID weights
  Serial.print("Correction Value: ");
  Serial.println(correctionValue);
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
  //motorLeft.setSpeed(leftSpeed);
  //motorRight.setSpeed(rightSpeed);
  analogWrite (E1,leftSpeed);      //PWM Speed Control
  digitalWrite(M1,HIGH);    
  analogWrite (E2,rightSpeed);    
  digitalWrite(M2,HIGH);
  Serial.print("L: ");  
  Serial.print(leftSpeed);
  Serial.print("    ");
  Serial.print("R: ");
  Serial.println(rightSpeed);

  Serial.println(correctionValue);
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
  
  //motorRight.run(FORWARD);
  //motorLeft.run(FORWARD);
 
  delay(20);

/*
  Serial.print("L: ");  
  Serial.print(leftSpeed);
  Serial.print("    ");
  Serial.print("R: ");
  Serial.println(rightSpeed);

  Serial.println(correctionValue);
  */
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
