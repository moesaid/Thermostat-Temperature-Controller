#include "TaskLogSerial.h"
#include "Shared/State.h"
#include "Config.h"

void taskLogSerial()
{
    static uint32_t lastMs = 0;
    const uint32_t now = millis();
    if (now - lastMs < LOG_INTERVAL_MS)
        return;
    lastMs = now;

    if (!gSensorOk || isnan(gCurrentTemperature) || isnan(gCurrentHumidity))
    {
        Serial.println(F("No valid data to log."));
        return;
    }

    Serial.print(F("Temperature: "));
    Serial.print(gCurrentTemperature, 1);
    Serial.println(F(" °C"));

    Serial.print(F("Humidity   : "));
    Serial.print(gCurrentHumidity, 1);
    Serial.println(F(" %"));
}
