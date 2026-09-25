# ESP32 Debug Toolkit for Escendo #

## Description ##
- The kit is used to test peripheral devices such as sensors, displays, etc.
- It can be used as quick test for quality control or competition day debug

## How to use ##
- Include the plugin header file into the main code
- Upload and connect the devices as described inside the plugin

## How to develop ##
- Create a header file name "Device_plugin.h" (for example "MPU6500_plugin.h")
- In the header file, write 2 functions: setup_device() and loop_device(), which correspond to setup() and loop() in a normal program.
- Write the instruction clearly using comments inside the file
- Update the device in README.md, including name, interface, dependencies
- Create a Pull Request

## Supported device list ##
| Device name | Interface | Dependencies |
| :---     | :---    | :---     |
| MPU6500 | I2C | MPU9250_WE by Wolfgang |
