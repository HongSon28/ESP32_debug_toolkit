
/*
 * ESP32 Debug Toolkit for Escendo
 *
 * Select ONE device to test by changing ACTIVE_PLUGIN.
 *
 * 1 = MPU6500 IMU Sensor
 * 2 = MQ135 Air Quality Sensor
 * 3 = BH1750 Ambient Light Sensor
 * 4 = KY-002 Vibration Sensor
 * 5 = IR Transmitter and Receiver
 * 6 = YL69 Soil Moisture Sensor
 * 7 = WS2812 RGB LED 4x4 Matrix
 *
 * Serial Monitor: 115200 baud
 */

#define ACTIVE_PLUGIN 1

// Include only the selected plugin
#if ACTIVE_PLUGIN == 1
  #include <Wire.h>
  #include "MPU6500_plugin.h"

#elif ACTIVE_PLUGIN == 2
  #include "MQ135_plugin.h"

#elif ACTIVE_PLUGIN == 3
  #include <Wire.h>
  #include "BH1750_plugin.h"

#elif ACTIVE_PLUGIN == 4
  #include "KY002_plugin.h"

#elif ACTIVE_PLUGIN == 5
  #include "IR_plugin.h"

#elif ACTIVE_PLUGIN == 6
  #include "YL69_plugin.h"

#elif ACTIVE_PLUGIN == 7
  #include "WS2812_plugin.h"

#else
  #error "Invalid ACTIVE_PLUGIN selection!"
#endif

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("==========================");
  Serial.println(" ESP32 Debug Toolkit");
  Serial.println("==========================");

  // Initialize I2C for I2C sensors
#if ACTIVE_PLUGIN == 1 || ACTIVE_PLUGIN == 3
  Wire.begin();
#endif

  // Initialize selected device
  setup_device();
}

void loop() {
  // Run selected device test
  loop_device();
}
