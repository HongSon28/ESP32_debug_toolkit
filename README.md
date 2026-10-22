# ESP32 Debug Toolkit for Escendo #

## Description ##
- The kit is used to test peripheral devices such as sensors, displays, etc.
- It can be used as quick test for quality control or competition day debug
- Supports various ESP32-compatible sensors, communication modules, and RGB LEDs.

## How to use ##
- Include the plugin header file into the main code
- Upload and connect the devices as described inside the plugin
- Open the Serial Monitor at 115200 baud to view the debugging output
- Test one plugin at a time to avoid function conflicts

## How to develop ##
- Create a header file name "Device_plugin.h" (for example "MPU6500_plugin.h")
- In the header file, write 2 functions: setup_device() and loop_device(), which correspond to setup() and loop() in a normal program.
- Write the instruction clearly using comments inside the file
- Update the device in README.md, including name, interface, dependencies
- Create a Pull Request

## Supported device list ##
| Device name | Interface | Dependencies |
| :--- | :--- | :--- |
| MPU6500 | I2C | MPU9250_WE by Wolfgang |
| MQ135 Air Quality Sensor | Analog (ADC) | None |
| BH1750 Ambient Light Sensor | I2C | BH1750 by Christopher Laws |
| KY-002 Vibration Sensor | Digital GPIO | None |
| IR Transmitter and Receiver | Digital GPIO (IR) | IRremote by Armin Joachimsmeyer |
| YL69 Soil Moisture Sensor | Analog (ADC) | None |
| WS2812 RGB LED 4x4 Matrix | Digital GPIO | Adafruit NeoPixel |

## Important Notes ##
- Ensure that all sensor connections are compatible with the ESP32's 3.3V GPIO logic.
- Do not connect 5V sensor outputs directly to ESP32 GPIO pins.
- Some modules may require an external power supply or voltage level shifting.
- Install the required libraries through the Arduino IDE Library Manager before uploading.
- Refer to the comments inside each plugin header file for wiring instructions and usage.
