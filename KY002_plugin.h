#pragma once
/* KY-002 vibration switch (ESP32).
   Typical 3-pin module: + -> 3.3V, - -> GND, S -> GPIO27.
   This is a mechanical vibration SWITCH, not an acceleration sensor.
   Some variants have opposite polarity; verify by tapping the module.
   Dependencies: ESP32 Arduino core only.
*/
#include <Arduino.h>
const int KY002_PIN = 27;
int ky002_last = HIGH;
void setup_device() {
  pinMode(KY002_PIN, INPUT_PULLUP);
  ky002_last = digitalRead(KY002_PIN);
  Serial.println("KY-002 ready; tap the module to observe transitions");
}
void loop_device() {
  int state = digitalRead(KY002_PIN);
  if (state != ky002_last) {
    Serial.printf("KY-002 transition: %s\n", state == LOW ? "LOW" : "HIGH");
    ky002_last = state;
  }
  delay(5);
}
