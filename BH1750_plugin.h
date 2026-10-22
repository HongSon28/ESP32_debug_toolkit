#pragma once
/* BH1750 ambient light sensor (ESP32).
   Wiring: VCC -> 3.3V, GND -> GND, SDA -> GPIO21, SCL -> GPIO22.
   ADDR -> GND/default for 0x23; ADDR -> 3.3V for 0x5C.
   Dependencies: BH1750 by Christopher Laws (Arduino Library Manager), Wire.
   Assumes typical 3.3V-compatible breakout.
*/
#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>
BH1750 bh1750;
bool bh1750_ok = false;
void setup_device() {
  Wire.begin(21,22);
  bh1750_ok = bh1750.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23, &Wire);
  Serial.println(bh1750_ok ? "BH1750 ready" : "BH1750 not found; check wiring/address");
}
void loop_device() {
  if (bh1750_ok) {
    float lux = bh1750.readLightLevel();
    if (lux < 0) Serial.println("BH1750 read error");
    else Serial.printf("Illuminance: %.1f lx\n",lux);
  }
  delay(1000);
}
