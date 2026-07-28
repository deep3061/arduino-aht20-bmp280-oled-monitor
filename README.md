# Arduino Environmental Monitoring System

An Arduino Uno environmental monitoring system using an AHT20 and BMP280 sensor module with a 0.96-inch SSD1306 OLED display.

The system measures temperature, humidity, and atmospheric pressure, then displays the readings on the OLED and in the Arduino Serial Monitor.


## Project Overview

This project was built to practise embedded programming, sensor integration, I2C communication, OLED display control, breadboard prototyping, hardware troubleshooting, and technical documentation.

The AHT20, BMP280, and OLED all communicate through the Arduino Uno's shared I2C bus.

## Features

- Measures ambient temperature using the AHT20
- Measures relative humidity using the AHT20
- Measures temperature using the BMP280
- Measures atmospheric pressure using the BMP280
- Displays live readings on a 0.96-inch OLED
- Sends readings to the Serial Monitor
- Updates the readings every two seconds
- Detects whether the OLED and sensors initialize correctly
- Uses multiple devices on the same I2C bus

## Hardware Used

- Arduino Uno R3
- AHT20 and BMP280 combined sensor module
- 0.96-inch 128 x 64 SSD1306 OLED display
- Breadboard
- Jumper wires
- USB cable

## Software and Libraries

- Arduino IDE
- Arduino C++
- Wire library
- Adafruit AHTX0
- Adafruit BMP280 Library
- Adafruit SSD1306
- Adafruit GFX Library
- Adafruit Unified Sensor
- Adafruit BusIO

## Wiring

### AHT20 + BMP280 Sensor Module

| Sensor Pin | Arduino Uno |
|---|---|
| VDD | 3.3V |
| GND | GND |
| SDA | A4 or SDA |
| SCL | A5 or SCL |

### OLED Display

| OLED Pin | Arduino Uno |
|---|---|
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

On the Arduino Uno:

- A4 = SDA
- A5 = SCL

The dedicated SDA and SCL pins are internally connected to A4 and A5. This means the OLED and sensor can share the same I2C bus.

## I2C Addresses

Typical device addresses are:

| Device | Address |
|---|---|
| AHT20 | 0x38 |
| OLED | 0x3C |
| BMP280 | 0x76 or 0x77 |

An I2C scanner can be used to confirm the addresses before running the full program.

## How the System Works

1. The Arduino initializes the I2C bus.
2. The OLED, AHT20, and BMP280 are initialized.
3. The AHT20 measures temperature and humidity.
4. The BMP280 measures temperature and atmospheric pressure.
5. The Arduino prints the readings to the Serial Monitor.
6. The OLED displays the latest values.
7. The readings update every two seconds.

## OLED Output

The display shows:

- AHT20 temperature
- Relative humidity
- BMP280 temperature
- Atmospheric pressure

Example output:

    ENVIRONMENT MONITOR
    Temp: 24.6 C
    Humidity: 58.2 %
    BMP Temp: 24.9 C
    Pressure: 1012 hPa

## Installation

Install the required libraries through:

Arduino IDE > Sketch > Include Library > Manage Libraries

Install:

- Adafruit AHTX0
- Adafruit BMP280 Library
- Adafruit SSD1306
- Adafruit GFX Library
- Adafruit Unified Sensor
- Adafruit BusIO

## Running the Project

1. Complete the wiring.
2. Open the Arduino sketch.
3. Select Tools > Board > Arduino Uno.
4. Select the correct USB port.
5. Upload the sketch.
6. Open Serial Monitor at 9600 baud.
7. Confirm the sensor readings appear on both the OLED and Serial Monitor.

## Troubleshooting

### Arduino Port Not Found

The Arduino IDE may try to use an old port that no longer exists.

Example error:

    cannot open port /dev/cu.usbmodem1101

Fix:

1. Disconnect and reconnect the Arduino.
2. Open Tools > Port.
3. Select the currently available Arduino port.
4. Upload again.

### OLED Did Not Display Data

The OLED did not operate correctly when powered from 3.3V.

The issue was resolved by connecting:

    OLED VCC -> Arduino 5V

The sensor module remained powered from 3.3V.

### Shared I2C Bus

The sensor and OLED both use the same SDA and SCL lines.

Correct wiring:

    Sensor SDA -> A4
    OLED SDA -> A4
    Sensor SCL -> A5
    OLED SCL -> A5

The sensor may also use the dedicated SDA and SCL pins because they are connected internally to A4 and A5.

### OLED Address

Most OLED modules use 0x3C. Some use 0x3D.

If the display remains blank, run an I2C scanner and confirm the address.

## Testing Performed

- Tested the OLED independently
- Tested the sensor module independently
- Confirmed the OLED works from the Arduino 5V pin
- Confirmed the sensor works from the Arduino 3.3V pin
- Verified both devices operate on the same I2C bus
- Confirmed temperature, humidity, and pressure readings
- Confirmed the OLED updates repeatedly
- Confirmed Serial Monitor output
- Verified device initialization messages
- Troubleshot USB port selection and OLED power issues

## Skills Demonstrated

- Arduino programming
- C++ programming
- Embedded systems
- Sensor testing
- I2C communication
- OLED integration
- Breadboard wiring
- Hardware troubleshooting
- Serial debugging
- Library integration
- Technical documentation

## Future Improvements

- Add an SD card for data logging
- Save readings in CSV format
- Add minimum and maximum measurements
- Add temperature and humidity warning thresholds
- Add a buzzer or LED alarm
- Add a real-time clock module
- Design a custom PCB
- Create a 3D-printed enclosure
- Add Wi-Fi using an ESP32
- Build a browser-based monitoring dashboard

## Project Status

The prototype is complete and operational.

## Author

Rubbal Sandhu

Computer Science student interested in embedded systems, IoT, robotics, AI, and laboratory prototyping.
