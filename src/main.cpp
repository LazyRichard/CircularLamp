#include <Arduino.h>
#include "NeoPixelBrightnessBus.h"
#include "NeoPixelAnimator.h"

/*
 * Serial
 */
const unsigned long BAUDRATE = 9600;

/*
 * WS2813b
 */
const uint16_t PANEL_WIDTH = 16;
const uint16_t PANEL_HEIGHT = 10;

const uint16_t PIXEL_COUNT = PANEL_WIDTH * PANEL_HEIGHT;
const uint8_t PIXEL_PIN = D4;

NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp8266AsyncUart1Ws2813Method> strip(PIXEL_COUNT, PIXEL_PIN);
NeoTopology<ColumnMajorAlternatingLayout> topo(PANEL_WIDTH, PANEL_HEIGHT);
NeoPixelAnimator animations(PIXEL_COUNT, NEO_CENTISECONDS);

void SetupAnimationSet(void);

/*
 * COLOR
 */
RgbColor red(128, 0, 0);
RgbColor green(0, 128, 0);
RgbColor blue(0, 0, 128);
RgbColor white(128);

uint16_t led = 0;

const uint8_t MIN_BRIGHTNESS = 50;
const uint8_t MAX_BRIGHTNESS = 150;

uint8_t glob_brightness = MIN_BRIGHTNESS;
bool direction = false;

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
  Serial.begin(BAUDRATE);
  while(!Serial); // Wait for serial attach

  // NeoPixel begin
  Serial.println(F("Initialize strip..."));
  strip.Begin();

  for(uint16_t pix = 0; pix < PIXEL_COUNT; pix++) {
    RgbColor color = RgbColor(random(255), random(255), random(255));
    strip.SetPixelColor(pix, color);
  }

  Serial.println(F("NodeMCU ready!"));
}

void loop() {
  // Serial information
  if (millis() - PrevTime_info > INTERVAL_INFO) {
    PrevTime_info = millis();
    Serial.print(F("TIME: ")); Serial.println(millis());
  }

  // Animate phase
  if (animations.IsAnimating()) {
    animations.UpdateAnimations();
  } else {
    Serial.println(F("Setup Nest Set..."));
    SetupAnimationSet();
  }

  // Global brightness
  if ((millis() - PrevTime_brightness > INTERVAL_BRIGHTNESS) && strip.CanShow()) {
    PrevTime_brightness = millis();

    if (direction) {
      glob_brightness = glob_brightness - 10;
    } else {
      glob_brightness = glob_brightness + 10;
    }

    if (glob_brightness >= MAX_BRIGHTNESS) {
      direction = true;
    } else if (glob_brightness <= MIN_BRIGHTNESS) {
      direction = false;
    }

    strip.SetBrightness(glob_brightness);
  }

  // Action phase
  if (strip.CanShow()) {
    strip.Show();
  }

}

void serialEvent() {
  String str = Serial.readString();

  Serial.print(str);
}

void SetupAnimationSet() {
  for(uint16_t pix = 0; pix < PIXEL_COUNT; pix++) {
    const uint8_t peak = 255;

    uint16_t time = random(100, 400);

    RgbColor originalColor = strip.GetPixelColor(pix);
    RgbColor targetColor = RgbColor(random(peak), random(peak), random(peak));

    AnimEaseFunction easing;

    switch (random(3)) {
      case 0:
        easing = NeoEase::CubicIn;
        break;
      case 1:
        easing = NeoEase::CubicOut;
        break;
      case 2:
        easing = NeoEase::QuarticInOut;
        break;
    }

    AnimUpdateCallback animUpdate = [=](const AnimationParam& param) {
      float progress = easing(param.progress);

      RgbColor updatedColor = RgbColor::LinearBlend(originalColor, targetColor, progress);
      strip.SetPixelColor(pix, updatedColor);
    };

    animations.StartAnimation(pix, time, animUpdate);
  }
}