#pragma once
/* IR transmitter + demodulating receiver loopback (ESP32).
   Receiver module: VCC -> 3.3V (only if rated), GND -> GND, OUT -> GPIO26.
   Transmitter: GPIO25 -> suitable transistor/driver -> IR LED + resistor.
   Do NOT drive a high-current IR LED directly from GPIO25.
   Place TX and RX facing each other; use 38kHz receiver (e.g. VS1838B).
   Dependencies: IRremote by Armin Joachimsmeyer (Arduino Library Manager).
   Sends NEC 0x34 to address 0x00 once per 2 seconds; prints decoded frames.
*/
#include <Arduino.h>
#include <IRremote.hpp>
const uint8_t IR_RX_PIN = 26;
const uint8_t IR_TX_PIN = 25;
unsigned long ir_last_send = 0;
void setup_device() {
  IrReceiver.begin(IR_RX_PIN, ENABLE_LED_FEEDBACK);
  IrSender.begin(IR_TX_PIN);
  Serial.println("IR TX/RX ready; face transmitter toward receiver");
}
void loop_device() {
  if (IrReceiver.decode()) {
    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.resume();
  }
  if (millis() - ir_last_send >= 2000) {
    ir_last_send = millis();
    IrSender.sendNEC(0x00, 0x34, 0);
    Serial.println("IR sent: NEC address 0x00 command 0x34");
  }
  delay(10);
}
