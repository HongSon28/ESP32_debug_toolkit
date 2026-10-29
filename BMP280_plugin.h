/*  This script uses the BMP280 module to print out temperature, 
    atmospheric pressure, and altitude estimate
*/

#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp; // create BMP280 instance

void setup_device() {

  Serial.begin(115200);

  while (!Serial);   // Do nothing if no serial port is opened

  Serial.println("BMP280 test");

  unsigned status;
  
  // default I2C address of the BMP280 is 0x76
  status = bmp.begin(0x76);
  if (!status) {
    Serial.println("Could not find a valid BMP280 sensor, check wiring or try a different address!");
    while (1);
  }

  // Choose how the sensor takes and smooths measurements.
  // More sampling reduces random noise but takes more time and power.
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     // Keep measuring automatically.
                  Adafruit_BMP280::SAMPLING_X2,     // Temperature: 2x sampling for less noise.
                  Adafruit_BMP280::SAMPLING_X16,    // Pressure: 16x sampling for less noise.
                  Adafruit_BMP280::FILTER_X16,      // Smooth sudden changes; responds more slowly.
                  Adafruit_BMP280::STANDBY_MS_500); // Rest 500 ms between measurement cycles.
}

void loop_device() {
    Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));

    /* 
    readAltitude takes the sea-level adjusted pressure in hPa to estimate altitude.
    Singapore's sea-level adjusted pressure is approximately 1012 hPa.
    */
    Serial.print(bmp.readAltitude(1013.25)); 
    Serial.println(" m");

    Serial.println();
    delay(2000);
}