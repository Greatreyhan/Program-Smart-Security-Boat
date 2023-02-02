
int Sensor = 2;     // RCWL-0516 Input Pin
int LED = 13;       // LED Output Pin

float sensorval = 0;  // RCWL-0516 Sensor Value


void setup() {
  pinMode (Sensor, INPUT);  // RCWL-0516 as input
  pinMode (LED, OUTPUT);    // LED as OUTPUT
  digitalWrite(LED, LOW);   // Turn LED Off
  Serial.begin(9600);
}

void loop(){

  sensorval = digitalRead(Sensor);  // Read Sensor value
  Serial.println(sensorval);
  if (sensorval == HIGH) {        
    digitalWrite(LED, HIGH);  // Turn LED On
  }
  else{
    digitalWrite(LED, LOW);  // Turn LED On
  }
}
