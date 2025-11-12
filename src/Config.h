#pragma once
#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>

// ---- Pins / Devices ----
constexpr uint8_t PIN_DHT = 2;
constexpr uint8_t DHT_TYPE = DHT22;

constexpr uint8_t LCD_ADDR = 0x27;
constexpr uint8_t LCD_COLS = 20;
constexpr uint8_t LCD_ROWS = 4;

constexpr uint8_t PIN_RELAY_HEAT = 5;
constexpr uint8_t PIN_RELAY_FAN = 6;

// Active low relays (IN=LOW => ON)
constexpr bool RELAY_ACTIVE_LOW = true;

// ---- Control parameters ----
constexpr float SETPOINT_C = 35.0f;  // °C
constexpr float HYSTERESIS_C = 0.5f; // half-band
constexpr uint32_t MIN_ON_MS = 60UL * 1000UL;
constexpr uint32_t MIN_OFF_MS = 60UL * 1000UL;

// ---- Task cadences (default; sensor interval is set from DHT) ----
constexpr uint32_t DISPLAY_INTERVAL_MS = 1000;
constexpr uint32_t LOG_INTERVAL_MS = 2000;
constexpr uint32_t CONTROL_INTERVAL_MS = 500;
