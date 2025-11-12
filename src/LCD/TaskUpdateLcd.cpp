#include "TaskUpdateLcd.h"
#include "Shared/Devices.h"
#include "Shared/State.h"
#include "Config.h"

/**
 * @brief Periodically updates the LCD with:
 *  Line 0: Current Temp and Target Temp (same line)
 *  Line 1: Humidity %
 */
void taskUpdateLcd()
{
    static uint32_t lastMs = 0;
    const uint32_t now = millis();

    // Run only every DISPLAY_INTERVAL_MS
    if (now - lastMs < DISPLAY_INTERVAL_MS)
        return;
    lastMs = now;

    // Validate device and data
    if (!gLcdReady)
        return;
    if (!gSensorOk || isnan(gCurrentTemperature) || isnan(gCurrentHumidity))
        return;

    // -----------------------------------------------------------------
    // LINE 0: Current temperature + target (setpoint)
    // Example:  Temp: 23.5°C  | Set: 24.0°C
    // -----------------------------------------------------------------
    gLcd.setCursor(0, 0);
    gLcd.print(F("T: "));

    char tbuf[8];
    dtostrf(gCurrentTemperature, 5, 1, tbuf);
    gLcd.print(tbuf);
    // gLcd.print((char)223);
    gLcd.print(F("C "));

    gLcd.print(F("S: "));
    char sbuf[8];
    dtostrf(SETPOINT_C, 5, 1, sbuf);
    gLcd.print(sbuf);
    // gLcd.print((char)223);
    gLcd.print('C');
    gLcd.print(F("   ")); // pad to overwrite old chars if shorter text

    // -----------------------------------------------------------------
    // LINE 1: Humidity
    // Example:  Hum: 45.7%
    // -----------------------------------------------------------------
    gLcd.setCursor(0, 1);
    gLcd.print(F("Hum: "));

    char hbuf[8];
    dtostrf(gCurrentHumidity, 5, 1, hbuf);
    gLcd.print(hbuf);
    gLcd.print('%');
    gLcd.print(F("     "));
}
