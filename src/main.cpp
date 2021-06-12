/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include "./sensors/Sensors.hpp"

Sensors sensors = Sensors(0x76, 0x28, 1013.25);

void setup()
{
  Serial.begin(9600);
  delay(2000);
  sensors.begin();
}

void loop()
{
  sensors.print_data();
  delay(2000);
}