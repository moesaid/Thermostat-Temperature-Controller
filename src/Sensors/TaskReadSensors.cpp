#include "TaskReadSensors.h"
#include "Shared/Devices.h"
#include "Shared/State.h"
#include "Config.h"

bool readSensorsOnce(float &t, float &h)
{
    sensors_event_t ev;

    gDht.temperature().getEvent(&ev);
    if (isnan(ev.temperature))
        return false;
    t = ev.temperature;

    gDht.humidity().getEvent(&ev);
    if (isnan(ev.relative_humidity))
        return false;
    h = ev.relative_humidity;

    return true;
}

void taskReadSensors()
{
    static uint32_t lastMs = 0;
    const uint32_t now = millis();
    if (now - lastMs < gReadIntervalMs)
        return;
    lastMs = now;

    float t = NAN, h = NAN;
    if (readSensorsOnce(t, h))
    {
        gSensorOk = true;
        gCurrentTemperature = t;
        gCurrentHumidity = h;
    }
    else
    {
        gSensorOk = false;
        Serial.println(F("Sensor read error"));
        if (gLcdReady)
        {
            gLcd.setCursor(0, 2);
            gLcd.print(F("Read error          "));
            gLcd.setCursor(0, 3);
            gLcd.print(F("Check wiring/pullup "));
        }
    }
}
