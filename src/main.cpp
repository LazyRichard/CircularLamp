#include <Arduino.h>

#include <Encoder.h>
#include "NeoPixelBrightnessBus.h"
#include "NeoPixelAnimator.h"

/*
 * Serial
 */
const unsigned long BAUDRATE = 9600;

/*
 * FLAGS
 */
volatile bool flag_btn = false;
volatile bool flag_rot = false;
volatile bool flag_change_anim = false;

/*
 * Rotary encoder
 */
Encoder enc(D1, D2);
uint8_t PIN_BTN = D3;

const long ROT_MIN_VALUE = 0;
const long ROT_MAX_VALUE = 255;

void btn_pressed();

long pos_old = -999;

/*
 * WS2813b
 */
const uint16_t PANEL_WIDTH = 17;
const uint16_t PANEL_HEIGHT = 10;

const uint16_t TILE_WIDTH = 2;
const uint16_t TILE_HEIGHT = 2;

const uint16_t PIXEL_COUNT = PANEL_WIDTH * PANEL_HEIGHT;
const uint8_t PIXEL_PIN = D4;

const uint16_t ANIMATION_CHANNEL = PIXEL_COUNT;

NeoPixelBrightnessBus<NeoGrbFeature, NeoEsp8266AsyncUart1Ws2813Method> strip(PIXEL_COUNT, PIXEL_PIN);
NeoGamma<NeoGammaTableMethod> colorGamma;
NeoTopology<ColumnMajorAlternatingLayout> topo(PANEL_WIDTH, PANEL_HEIGHT);
NeoPixelAnimator animations(ANIMATION_CHANNEL, NEO_CENTISECONDS);

uint8_t anim_selector = 0;
const uint8_t NUM_ANIMATION = 4;

void fadeOutAnimationSet(void);
void funRandomAnimationSet(void);
void tileRandomAnimationSet(void);
void zTetrominoRandomAnimationSet(void);

void (*animationStartSet)() = &funRandomAnimationSet;

/*
 * COLOR
 */
const uint8_t MIN_BRIGHTNESS = 20;
const uint8_t MAX_BRIGHTNESS = 150;

const uint8_t PEAK_COLOR_VAL = 255;

/*
 * TIME
 */
unsigned long PrevTime_strip = 0;
unsigned long PrevTime_info = 0;
volatile unsigned long PrevTime_btn = 0;
unsigned long PrevTime_brightness = 0;
unsigned long PrevTime_animation = 0;

const unsigned long INTERVAL_STRIP = 50;
const unsigned long INTERVAL_INFO = 500;
const unsigned long MIN_INTERVAL_BTN = 400;
const unsigned long INTERVAL_BRIGHTNESS = 500;
const unsigned long INTERVAL_ANIMATION = 2500;

void setup() {
  // Serial
  do {
    Serial.begin(BAUDRATE);
    delay(200);
  } while (!Serial);
  Serial.println(F("INFO: Serial initialize complete"));

  // Rotary encoder
  pinMode(PIN_BTN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PIN_BTN), btn_pressed, RISING);

  // NeoPixel begin
  Serial.println(F("INFO: Initialize strip..."));
  strip.Begin();

  strip.SetBrightness(MIN_BRIGHTNESS);
  for(uint16_t pix = 0; pix < PIXEL_COUNT; pix++) {
    RgbColor color = RgbColor(0);
    strip.SetPixelColor(pix, color);
  }

  Serial.println(F("INFO: NodeMCU ready!"));
}

void loop() {
  // Serial information
  if (millis() - PrevTime_info > INTERVAL_INFO) {
    PrevTime_info = millis();
    Serial.print(F("INFO: TIME-")); Serial.print(millis());
    Serial.print(F(" BRIGHT-")); Serial.print(strip.GetBrightness());
    Serial.print(F(" ANIMATION-")); Serial.println(anim_selector);
  }

  // Button event
  if (flag_btn) {
    flag_btn = false;

    flag_change_anim = true;

    anim_selector = (anim_selector + 1) % NUM_ANIMATION;

    Serial.print(F("INFO: Next animation set-"));
    switch (anim_selector) {
      default:
      case 0:
        Serial.println(F("FunRandomAnimation"));
        animationStartSet = &funRandomAnimationSet;
        break;
      case 1:
        Serial.println(F("TileRandomAnimation"));
        animationStartSet = &tileRandomAnimationSet;
        break;
      case 2:
        Serial.println(F("ZminoRandomAnimation"));
        animationStartSet = &zTetrominoRandomAnimationSet;
        break;
      case 3:
        Serial.println(F("FadeoutAnimation"));
        animationStartSet = &fadeOutAnimationSet;
        break;
    }
  }

  // Animate phase
  if (flag_change_anim) {
    flag_change_anim = false;

    animations.StopAll();
  } else if ((millis() - PrevTime_animation > INTERVAL_ANIMATION) || !animations.IsAnimating()) {
    PrevTime_animation = millis();

    animationStartSet();
  } else if (animations.IsAnimating()) {
    animations.UpdateAnimations();
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
      Serial.print(F("DEBUG: ROT-")); Serial.println(pos_old);
  }

  // Serial event
  if (Serial.available()) {
    String str = Serial.readString();

    Serial.print(F("INFO: MSG-")); Serial.print(str);
  }
}

void btn_pressed() {
  if (millis() - PrevTime_btn > MIN_INTERVAL_BTN) {
    PrevTime_btn = millis();
    flag_btn = true;

    Serial.println(F("DEBUG: Button Pressed"));
  } else {
    Serial.println(F("WARN: DETECTED BUTTON PRESSED. BUT PRESSED TOO QUICKLY. IGNORE IT"));
  }
}

void fadeOutAnimationSet() {
  uint16_t time = 200;

  for (uint16_t pix = 0; pix < PIXEL_COUNT; pix++) {
    RgbColor originalColor = strip.GetPixelColor(pix);
    RgbColor targetColor = RgbColor(0);

    AnimUpdateCallback animUpdate = [=](const AnimationParam& param) {
      RgbColor updatedColor = RgbColor::LinearBlend(originalColor, targetColor, param.progress);

      strip.SetPixelColor(pix, updatedColor);
    };

    animations.StartAnimation(pix, time, animUpdate);
  }
}

void funRandomAnimationSet() {
  for (uint16_t pix = 0; pix < PIXEL_COUNT; pix++) {
    uint16_t time = random(100, 400);

    RgbColor originalColor = strip.GetPixelColor(pix);
    RgbColor targetColor = colorGamma.Correct(RgbColor(random(PEAK_COLOR_VAL), random(PEAK_COLOR_VAL), random(PEAK_COLOR_VAL)));
    AnimEaseFunction easing;

    switch (random(3)) {
      case 0:
        easing = NeoEase::CubicIn;
        break;
      case 1:
        easing = NeoEase::CubicOut;
        break;
      case 2:
        easing = NeoEase::QuadraticInOut;
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

void tileRandomAnimationSet() {

  const uint16_t TILE_WIDTH = 2;
  const uint16_t TILE_HEIGHT = 2;

  int anim_index = 0;
  for (uint16_t width = 0; width < PANEL_WIDTH; width += TILE_WIDTH) {
    for (uint16_t height = 0; height < PANEL_HEIGHT; height += TILE_HEIGHT) {
      const uint16_t time = random(100, 400);

      RgbColor targetColor = colorGamma.Correct(RgbColor(random(PEAK_COLOR_VAL), random(PEAK_COLOR_VAL), random(PEAK_COLOR_VAL)));
      
      AnimEaseFunction easing;

      switch (random(3)) {
        case 0:
          easing = NeoEase::CubicIn;
          break;
        case 1:
          easing = NeoEase::CubicOut;
          break;
        case 2:
          easing = NeoEase::QuadraticInOut;
          break;
      }

      uint16_t limit_width = (width + TILE_WIDTH) > PANEL_WIDTH ? (width + TILE_WIDTH) : PANEL_WIDTH;
      uint16_t limit_height = (height + TILE_HEIGHT) > PANEL_HEIGHT ? (height + TILE_HEIGHT) : PANEL_HEIGHT;
      for (uint16_t width_seg = width; width_seg < limit_width; width_seg++) {
        for (uint16_t height_seg = height; height_seg < limit_height; height_seg++) {
          RgbColor originalColor = strip.GetPixelColor(topo.Map(width_seg, height_seg));

          AnimUpdateCallback animUpdate = [=](const AnimationParam& param) {
            float progress = easing(param.progress);

            RgbColor updatedColor = RgbColor::LinearBlend(originalColor, targetColor, progress);

            strip.SetPixelColor(topo.Map(width_seg, height_seg), updatedColor);
          };

          animations.StartAnimation(anim_index, time, animUpdate);
          anim_index++;
        }
      }
    }
  }
  Serial.print(F("DEBUG: TILE ANIMATION INDEX-")); Serial.println(anim_index);
}

void zTetrominoRandomAnimationSet() {

  const uint16_t TILE_WIDTH = 2;
  const uint16_t TILE_HEIGHT = 2;

  int anim_index = 0;
  for (uint16_t width = 0; width < PANEL_WIDTH; width++) {
    for (uint16_t height = 0; height < PANEL_HEIGHT; height++) {
      if (!(width % TILE_WIDTH) && !(height % TILE_HEIGHT)) {
        uint16_t time = random(100, 600);

        RgbColor targetColor = colorGamma.Correct(RgbColor(random(PEAK_COLOR_VAL), random(PEAK_COLOR_VAL), random(PEAK_COLOR_VAL)));

        AnimEaseFunction easing;

        switch (random(3)) {
          case 0:
            easing = NeoEase::CubicIn;
            break;
          case 1:
            easing = NeoEase::CubicOut;
            break;
          case 2:
            easing = NeoEase::QuadraticInOut;
            break;
        }

        uint16_t width_seg = width;
        uint16_t height_seg = height;
        
        for (uint16_t tile_width = 0; tile_width < TILE_WIDTH; tile_width++) {
          width_seg = (width_seg + tile_width) % PANEL_WIDTH;

          for (uint16_t tile_height = 0; tile_height < TILE_HEIGHT; tile_height++) {
            height_seg = (height_seg + tile_height) % PANEL_HEIGHT;

            RgbColor originalColor(strip.GetPixelColor(topo.Map(width_seg, height_seg)));

            AnimUpdateCallback animUpdate = [=](const AnimationParam& param) {
              float progress = easing(param.progress);

              RgbColor updatedColor = RgbColor::LinearBlend(originalColor, targetColor, progress);

              strip.SetPixelColor(topo.Map(width_seg, height_seg), updatedColor);

            };

            animations.StartAnimation(anim_index, time, animUpdate);
            anim_index++;
          }
        }
      }
    }
  }

  Serial.print(F("DEBUG: Zmino ANIMATION INDEX-")); Serial.println(anim_index);
}
