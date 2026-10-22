#pragma once
/* YL-69 resistive soil moisture probe + comparator module (ESP32).
   Module VCC -> 3.3V, GND -> GND, AO -> GPIO35; DO unused.
   Only use 3.3V supply if your board operates correctly at 3.3V.
   Readings depend on soil and board; calibrate air/dry and wet separately.
   Power probe only during measurements in long-term projects to limit corrosion.
   Dependencies: ESP32 Arduino core only.
*/
#include <Arduino.h>
const int YL69_PIN = 35;
void setup_device() {
  analogReadResolution(12);
  analogSetPinAttenuation(YL69_PIN, ADC_11db);
  Serial.println("YL-69 ready; compare dry vs wet readings");
}
void loop_device() {
  int raw = analogRead(YL69_PIN);
  Serial.printf("YL-69 raw: %d / 4095 (calibration required)\n",raw);
  delay(1000);
}
