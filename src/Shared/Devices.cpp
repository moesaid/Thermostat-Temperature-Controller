#include "Devices.h"
#include "Config.h"
#include "Shared/State.h"
#include "Relay/Relay.h"

DHT_Unified gDht(PIN_DHT, DHT_TYPE);
LiquidCrystal_I2C gLcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

// State defaults
bool gLcdReady = false;
bool gSensorOk = false;
float gCurrentTemperature = NAN;
float gCurrentHumidity = NAN;

bool gHeaterOn = false;
bool gFanOn = false;

uint32_t gLastHeaterToggleMs = 0;
uint32_t gLastFanToggleMs = 0;

uint32_t gReadIntervalMs = 2000; // will be set from DHT min_delay

void initSerial()
{
    Serial.begin(9600);
    while (!Serial)
    { /* Uno returns immediately */
    }
}

void initDht()
{
    gDht.begin();
    sensor_t s;
    gDht.temperature().getSensor(&s);
    // min_delay is µs; guard against 0
    uint32_t mdUs = s.min_delay ? s.min_delay : 2000000UL;
    gReadIntervalMs = mdUs / 1000UL;
}

void initLcd()
{
    gLcd.init();
    gLcd.backlight();
    gLcd.noCursor();
    gLcd.noBlink();
    gLcd.clear();

    // static labels once (no flicker)
    gLcd.setCursor(0, 0);
    gLcd.print(F("Temp:"));
    gLcd.setCursor(0, 1);
    gLcd.print(F("Hum :"));

    gLcd.setCursor(0, 2);
    gLcd.print(F("DHT22 Ready"));
    gLcd.setCursor(0, 3);
    gLcd.print(F("Int: "));
    gLcd.print(gReadIntervalMs);
    gLcd.print(F(" ms   "));

    gLcdReady = true;
}

void printSensorDetails()
{
    sensor_t s;

    gDht.temperature().getSensor(&s);
    Serial.println(F("---- Temperature Sensor ----"));
    Serial.print(F("Type: "));
    Serial.println(s.name);
    Serial.print(F("Driver Ver: "));
    Serial.println(s.version);
    Serial.print(F("ID: "));
    Serial.println(s.sensor_id);
    Serial.print(F("Max: "));
    Serial.print(s.max_value);
    Serial.println(F(" °C"));
    Serial.print(F("Min: "));
    Serial.print(s.min_value);
    Serial.println(F(" °C"));
    Serial.print(F("Resolution: "));
    Serial.print(s.resolution);
    Serial.println(F(" °C"));
    Serial.println();

    gDht.humidity().getSensor(&s);
    Serial.println(F("---- Humidity Sensor ----"));
    Serial.print(F("Type: "));
    Serial.println(s.name);
    Serial.print(F("Driver Ver: "));
    Serial.println(s.version);
    Serial.print(F("ID: "));
    Serial.println(s.sensor_id);
    Serial.print(F("Max: "));
    Serial.print(s.max_value);
    Serial.println(F(" %"));
    Serial.print(F("Min: "));
    Serial.print(s.min_value);
    Serial.println(F(" %"));
    Serial.print(F("Resolution: "));
    Serial.print(s.resolution);
    Serial.println(F(" %"));
    Serial.println();

    Serial.print(F("Read interval (ms): "));
    Serial.println(gReadIntervalMs);
}

void initRelays()
{
    pinMode(PIN_RELAY_HEAT, OUTPUT);
    pinMode(PIN_RELAY_FAN, OUTPUT);

    relayWrite(PIN_RELAY_HEAT, false);
    relayWrite(PIN_RELAY_FAN, false);

    gHeaterOn = false;
    gFanOn = false;
    gLastHeaterToggleMs = millis();
    gLastFanToggleMs = millis();
}
