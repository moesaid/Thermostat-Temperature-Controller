#pragma once
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Config.h"

// device singletons
extern DHT_Unified gDht;
extern LiquidCrystal_I2C gLcd;

// init functions
void initSerial();
void initDht();
void initLcd();
void printSensorDetails();
void initRelays();
