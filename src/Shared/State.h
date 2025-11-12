#pragma once
#include <Arduino.h>

// shared runtime state
extern bool gLcdReady;
extern bool gSensorOk;

extern float gCurrentTemperature; // latest good readings
extern float gCurrentHumidity;

extern bool gHeaterOn;
extern bool gFanOn;

extern uint32_t gLastHeaterToggleMs;
extern uint32_t gLastFanToggleMs;

// sensor read interval (populated from DHT metadata)
extern uint32_t gReadIntervalMs;
