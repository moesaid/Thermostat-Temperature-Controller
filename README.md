# Smart Temperature & Humidity Control System

This project is a **non-blocking, Arduino-based environmental controller** that automatically manages a heater and fan using real-time data from a **DHT22 sensor**. It displays temperature, humidity, and setpoint values on an **LCD1602/I2C display**, ensuring stable climate control through hysteresis and minimum on/off safety timers.

---

## Features
- Reads **temperature** and **humidity** using the DHT22 sensor
- Controls **heater** and **fan** via 2-channel relay module
- Implements **hysteresis control** to prevent relay chatter
- Enforces **minimum ON/OFF times** for relay protection
- Displays live **Temp, Setpoint, and Humidity** on LCD
- **Non-blocking code** using `millis()` for smooth multitasking
- Modular design with separate task files for easy maintenance

---

## Hardware Requirements
| Component | Quantity | Notes |
|------------|-----------|-------|
| Arduino Uno R3 | 1 | Main controller board |
| DHT22 / AM2302 | 1 | Temperature & humidity sensor |
| 2-Channel Relay Module | 1 | Controls heater and fan |
| LCD1602 with I2C Backpack | 1 | Display readings |
| Jumper Wires | - | For connections |
| 4.7kΩ Resistor | 1 | DHT22 pull-up resistor |
| Heater / Fan | 1 each | Controlled via relays |

---

## Pin Connections
| Device | Pin | Arduino |
|---------|-----|----------|
| DHT22 | VCC | 5V |
| DHT22 | DATA | D2 |
| DHT22 | GND | GND |
| Relay CH1 (Heater) | IN1 | D5 |
| Relay CH2 (Fan) | IN2 | D6 |
| LCD1602 | SDA | A4 |
| LCD1602 | SCL | A5 |
