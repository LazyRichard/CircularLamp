/* Read Quadrature Encoder
   Connect Encoder to Pins PinA, PinB, and +5V.

   Sketch by max wolf / www.meso.net
   v. 0.1 - very basic functions - mw 20061220

*/

int val;
const uint8_t PinA = 18;
const uint8_t PinB = 20;
const uint8_t GND = 19;

const unsigned long INTERVAL_ROTARY_ENCODER = 3;

typedef struct _RotaryEncoder {
    unsigned long last_update_ms = 0;
    bool a = false;
    bool b = false;
} RotaryEncoder;

volatile RotaryEncoder encoder;

void setup() {
    pinMode(PinA, INPUT_PULLUP);
    pinMode(PinB, INPUT_PULLUP);
    pinMode(GND, OUTPUT);
    digitalWrite(GND, LOW);

    Serial.begin(9600);

    attachInterrupt(digitalPinToInterrupt(PinA), encA, RISING);
    attachInterrupt(digitalPinToInterrupt(PinB), encB, RISING);

    Serial.println(F("Arduio ready!"));
}

void loop() {

}

void encA() {
    cli();
    if (millis() - encoder.last_update_ms > INTERVAL_ROTARY_ENCODER) {
        encoder.last_update_ms = millis();
        Serial.print(F("EventA-")); Serial.print(F("A: ")); Serial.print(digitalRead(PinA)); 
        Serial.print(F("B: ")); Serial.println(digitalRead(PinB));
    }
    sei();
}

void encB() {
    cli();
    if (millis() - encoder.last_update_ms > INTERVAL_ROTARY_ENCODER) {
        encoder.last_update_ms = millis();
        Serial.print(F("EventB-")); Serial.print(F("A: ")); Serial.print(digitalRead(PinA)); 
        Serial.print(F("B: ")); Serial.println(digitalRead(PinB));
    }
    sei();
}
