#include <Arduino.h>

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    Serial.println("LED_BUILTIN HIGH");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    Serial.println("LED_BUILTIN LOW");
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
}