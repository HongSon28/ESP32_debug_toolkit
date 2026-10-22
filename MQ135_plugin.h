#pragma once
/* MQ135 air-quality trend test (ESP32).
   Wiring: module VCC -> 5V (if required by your module), GND -> GND,
   AO -> voltage divider -> GPIO34. Example divider: AO--10k--GPIO34--20k--GND.
   Divider scales 5V to 3.33V; check actual module output and ESP32 ADC limits.
   DO is unused. Allow sensor to warm up; readings are NOT calibrated ppm/AQI.
   Never connect 5V AO/DO directly to ESP32 pins.
   Dependencies: ESP32 Arduino core only.
*/
#include <Arduino.h>
const int MQ135_PIN = 34;
void setup_device() {
  analogReadResolution(12);
  analogSetPinAttenuation(MQ135_PIN, ADC_11db);
  Serial.println("MQ135 ready (relative reading; warm up sensor)");
}
void loop_device() {
  int raw = analogRead(MQ135_PIN);
  int mv = analogReadMilliVolts(MQ135_PIN);
  Serial.printf("MQ135 ADC: %d / 4095, ESP32 pin: %d mV (uncalibrated)\n",raw,mv);
  delay(1000);
}
