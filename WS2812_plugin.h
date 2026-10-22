#pragma once
/* WS2812 / NeoPixel 4x4 matrix (16 LEDs), ESP32.
   DIN -> GPIO18 via 330-470 ohm resistor; GND -> ESP32 GND and PSU GND.
   Matrix 5V -> regulated 5V supply rated for LED current (up to ~1A full white).
   Add ~1000uF capacitor across 5V/GND near matrix; use 3.3-to-5V logic
   level shifter (74AHCT125 recommended) for reliable 5V operation.
   Do NOT feed LED 5V into ESP32 GPIO. Never power full matrix from GPIO.
   Dependencies: Adafruit NeoPixel (Arduino Library Manager).
*/
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
const int WS2812_PIN = 18;
const int WS2812_COUNT = 16;
Adafruit_NeoPixel pixels(WS2812_COUNT, WS2812_PIN, NEO_GRB + NEO_KHZ800);
uint8_t ws2812_step = 0;
void setup_device() {
  pixels.begin();
  pixels.setBrightness(35); // keep demo current low
  pixels.clear();
  pixels.show();
  Serial.println("WS2812 4x4 ready (16 pixels)");
}
void loop_device() {
  pixels.clear();
  uint32_t color = (ws2812_step % 3 == 0) ? pixels.Color(255,0,0) :
                   (ws2812_step % 3 == 1) ? pixels.Color(0,255,0) : pixels.Color(0,0,255);
  pixels.setPixelColor(ws2812_step % WS2812_COUNT, color);
  pixels.show();
  Serial.printf("Pixel %d illuminated\n", ws2812_step % WS2812_COUNT);
  ws2812_step++;
  delay(250);
}
