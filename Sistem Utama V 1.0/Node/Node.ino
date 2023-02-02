#include <Wire.h>
#include <I2C_Anything.h>

volatile float radar;
void setup()
{
  Serial.begin(115200);
  Wire.begin(D1, D2); 
}

void loop()
{
  Wire.requestFrom(8, 4); // reqeust 6 bytes from salve Uno #8
  I2C_readAnything (radar);
  Serial.print("Radar = ");
  Serial.println(radar, 2);
}
