#include <Arduino.h>

const unsigned long BAUDRATE = 9600;

void setup() {
  Serial.begin(BAUDRATE);
  
  Serial.println(F("NodeMCU ready!"));
}

void loop() {
  // put your main code here, to run repeatedly:
}