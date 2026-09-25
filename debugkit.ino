#include "MPU6500_plugin.h"

void setup() {
  Serial.begin(115200);
  Wire.begin();

  setup_device();
}

void loop() {
  // put your main code here, to run repeatedly:
  loop_device();
}
