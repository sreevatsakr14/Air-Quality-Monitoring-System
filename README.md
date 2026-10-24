# Air Quality Monitoring System

## Project Overview
This project monitors environmental air quality using an ESP32 and gas and dust sensors. It is designed to collect sensor readings and help users understand air-quality conditions.

## Technologies Used
- ESP32
- C/C++ (Arduino)
- MQ-2 Gas Sensor
- PM2.5/PM10 Dust Sensor
- GPS Module (NEO-6M)
- ThingSpeak

## Features
- Collects gas sensor readings.
- Monitors particulate matter, where supported by the selected dust sensor.
- Uses an ESP32 to process sensor data.
- Can send readings to ThingSpeak for visualization, if configured.

## Hardware Requirements
- ESP32 development board
- MQ-2 gas sensor
- Compatible dust sensor
- NEO-6M GPS module (if location tracking is implemented)
- Jumper wires and breadboard
- USB cable or suitable power supply

## Setup Instructions
1. Connect the sensors to the ESP32 according to the circuit design.
2. Install the required libraries in the Arduino IDE.
3. Configure the sensor pins and network settings.
4. Add your ThingSpeak configuration if cloud visualization is enabled.
5. Upload the firmware to the ESP32 and test the readings.

## Project Status
Update this section with the features you have implemented and tested.
