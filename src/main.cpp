#include <Arduino.h>

#include <Encoder.h>
#include "NeoPixelBrightnessBus.h"
#include "NeoPixelAnimator.h"

/*
 * Serial
 */
const unsigned long BAUDRATE = 9600;

/*
 * Rotary encoder
 */
Encoder enc(D1, D2);
uint8_t PIN_BTN = D3;

const long ROT_MIN_VALUE = 0;
const long ROT_MAX_VALUE = 255;

void btn_clicked();

bool flag_en = false;
bool flag_rot = false;
long pos_old = -999;

/*
 * WS2813b
 */
const uint16_t PANEL_WIDTH = 17;
const uint16_t PANEL_HEIGHT = 10;

const uint16_t PIXEL_COUNT = PANEL_WIDTH * PANEL_HEIGHT;
const uint8_t PIXEL_PIN = D4;

NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp8266AsyncUart1Ws2813Method> strip(PIXEL_COUNT, PIXEL_PIN);
NeoGamma<NeoGammaTableMethod> colorGamma;
NeoTopology<ColumnMajorAlternatingLayout> topo(PANEL_WIDTH, PANEL_HEIGHT);
NeoPixelAnimator animations(1, NEO_CENTISECONDS);

void SetupAnimationSet(void);

/*
 * COLOR
 */
const uint8_t MIN_BRIGHTNESS = 50;
const uint8_t MAX_BRIGHTNESS = 150;

/*
 * TIME
 */
unsigned long PrevTime_strip = 0;
unsigned long PrevTime_info = 0;
unsigned long PrevTime_brightness = 0;

const unsigned long INTERVAL_STRIP = 50;
const unsigned long INTERVAL_INFO = 500;
const unsigned long INTERVAL_BRIGHTNESS = 500;

void setup() {
  // Serial
  do {
    Serial.begin(BAUDRATE);
    delay(200);
  } while (!Serial);
  Serial.println(F("Serial initialize complete"));

  // Rotary encoder
  pinMode(PIN_BTN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_BTN), btn_clicked, RISING);

  // NeoPixel begin
  Serial.println(F("Initialize strip..."));
  strip.Begin();

  strip.SetBrightness(MIN_BRIGHTNESS);
  for(uint16_t pix = 0; pix < PIXEL_COUNT; pix++) {
    RgbColor color = RgbColor(0, 0, 0);
    strip.SetPixelColor(pix, colorGamma.Correct(color));
  }

  Serial.println(F("NodeMCU ready!"));
}

void loop() {
  // Serial information
  if (millis() - PrevTime_info > INTERVAL_INFO) {
    PrevTime_info = millis();
    Serial.print(F("TIME: ")); Serial.print(millis());
    Serial.print(F(" BRIGHT: ")); Serial.println(strip.GetBrightness());
  }

  // Animate phase
  if (animations.IsAnimating()) {
    animations.UpdateAnimations();
  } else {
    Serial.println(F("Setup Next Set..."));
    SetupAnimationSet();
  }

  // Global brightness
  if (flag_rot) {
    flag_rot = false; // clear rotary encoder event

    uint8_t brightness = (((float)(pos_old - ROT_MIN_VALUE) / (float)(ROT_MAX_VALUE - ROT_MIN_VALUE)) * (MAX_BRIGHTNESS - MIN_BRIGHTNESS)) + MIN_BRIGHTNESS;

    strip.SetBrightness(brightness);
  }

  // Action phase
  if (strip.CanShow()) {
    strip.Show();
  }

  // Rotary encoder
  long pos_new = enc.read();
  if (pos_old != pos_new) {
      flag_rot = true; // set rotary encoder event

      if (pos_new <= ROT_MIN_VALUE) {
          enc.write(ROT_MIN_VALUE);
      } else if (pos_new >= ROT_MAX_VALUE) {
          enc.write(ROT_MAX_VALUE);
      }

      pos_old = enc.read();
      Serial.print(F("ROT: ")); Serial.println(pos_old);
  }
}

void serialEvent() {
  String str = Serial.readString();

  Serial.print(str);
}

bool fade_in = true;

void SetupAnimationSet() {
  uint16_t time = 800;

  RgbColor originalColor = strip.GetPixelColor(0);
  RgbColor targetColor = RgbColor(0);

  if (fade_in) {
    targetColor = HslColor(random(360) / 360.0f, 1.0f, 0.25f);
  } else {
    targetColor = RgbColor(0);
  }

  AnimUpdateCallback animUpdate = [=](const AnimationParam& param) {
    RgbColor updatedColor = RgbColor::LinearBlend(originalColor, targetColor, param.progress);

    for (uint16_t pix = 0; pix < PIXEL_COUNT; pix++) {
      strip.SetPixelColor(pix, updatedColor);
    }
  };

  animations.StartAnimation(0, time, animUpdate);

  fade_in = !fade_in;
}

void btn_clicked() {
  cli();

  flag_en = !flag_en;
  Serial.print(F("BTN: ")); Serial.println(flag_en);

  sei();
}
