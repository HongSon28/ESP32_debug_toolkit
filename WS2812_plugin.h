
#pragma once

/*
 * WS2812 / NeoPixel 4x4 Matrix (16 LEDs), ESP32
 *
 * Wiring:
 * DIN -> GPIO18 via 330-470 ohm resistor
 * GND -> ESP32 GND and PSU GND
 * 5V  -> Regulated 5V supply (up to ~1A full white)
 *
 * Add ~1000uF capacitor across 5V/GND near matrix.
 * Use 3.3V-to-5V logic level shifter (74AHCT125 recommended).
 * Do NOT power the matrix from ESP32 GPIO.
 *
 * Dependencies: Adafruit NeoPixel (Arduino Library Manager)
 *
 * Available API:
 * setPixel(index, red, green, blue)
 * setPixelXY(x, y, red, green, blue)
 * setAll(red, green, blue)
 * setPattern(pattern)
 * clearMatrix()
 * showMatrix()
 *
 * LED index: 0-15
 * RGB values: 0-255
 */

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

const int WS2812_PIN = 18;
const int WS2812_COUNT = 16;

Adafruit_NeoPixel pixels(
  WS2812_COUNT,
  WS2812_PIN,
  NEO_GRB + NEO_KHZ800
);

// Store RGB colours for all 16 LEDs
uint8_t ledColors[16][3] = {
  {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 0},
  {255, 0, 255}, {0, 255, 255}, {255, 255, 255}, {255, 100, 0},
  {255, 100, 0}, {255, 255, 255}, {0, 255, 255}, {255, 0, 255},
  {255, 255, 0}, {0, 0, 255}, {0, 255, 0}, {255, 0, 0}
};

// Set colour of one LED (index 0-15)
void setPixel(int index, uint8_t r, uint8_t g, uint8_t b) {
  if (index < 0 || index >= WS2812_COUNT) return;

  ledColors[index][0] = r;
  ledColors[index][1] = g;
  ledColors[index][2] = b;
}

// Set LED using x,y coordinates (0-3)
// Assumes row-major, serpentine wiring
void setPixelXY(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
  if (x < 0 || x >= 4 || y < 0 || y >= 4) return;

  int index = (y % 2 == 0) ? y * 4 + x
                            : y * 4 + (3 - x);

  setPixel(index, r, g, b);
}

// Set all LEDs to the same colour
void setAll(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < WS2812_COUNT; i++) {
    setPixel(i, r, g, b);
  }
}

// Load a complete 16-LED RGB pattern
void setPattern(const uint8_t pattern[16][3]) {
  for (int i = 0; i < WS2812_COUNT; i++) {
    setPixel(i,
             pattern[i][0],
             pattern[i][1],
             pattern[i][2]);
  }
}

// Turn off all LEDs
void clearMatrix() {
  setAll(0, 0, 0);
}

// Update the physical LED matrix
void showMatrix() {
  for (int i = 0; i < WS2812_COUNT; i++) {
    pixels.setPixelColor(
      i,
      pixels.Color(
        ledColors[i][0],
        ledColors[i][1],
        ledColors[i][2]
      )
    );
  }

  pixels.show();
}

// Initialize the WS2812 matrix
void setup_device() {
  pixels.begin();
  pixels.setBrightness(35);

  clearMatrix();
  showMatrix();

  Serial.println("WS2812 4x4 Matrix ready");
  Serial.println("16 LEDs initialized");
  Serial.println("Custom RGB control enabled");
}

// Main loop: display the stored colour pattern
void loop_device() {
  showMatrix();
  delay(100);
}
