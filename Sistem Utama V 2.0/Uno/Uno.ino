#include <Wire.h>
#include <I2C_Anything.h>

int Sensor = 2;     // RCWL-0516 Input Pin
int LED = 13;       // LED Output Pin

struct
{
 float radar;

} response;



void setup()
{
  Serial.begin (115200);
  pinMode (Sensor, INPUT);  // RCWL-0516 as input
  pinMode (LED, OUTPUT);    // LED as OUTPUT
  digitalWrite(LED, LOW);   // Turn LED Off
  Wire.begin(8);                
  Wire.onRequest(requestEvent); 

}

void loop()
{

  Serial.println();
  response.radar = digitalRead(Sensor);  // Read Sensor value
  Serial.println(response.radar);
  if (response.radar == HIGH) {        
    digitalWrite(LED, HIGH);  // Turn LED On
  }
  else{
    digitalWrite(LED, LOW);  // Turn LED On
  }
  Serial.print("Radar = ");
  Serial.print(response.radar, 2);

}

void requestEvent ()
{
  I2C_writeAnything(response);
} 
