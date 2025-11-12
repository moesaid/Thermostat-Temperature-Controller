#include "TaskControlRelay.h"
#include "Config.h"
#include "Shared/State.h"
#include "Relay/Relay.h"

/**
 * @brief Controls heater and fan relays based on temperature readings.
 *
 * This function:
 *  - Runs periodically (non-blocking) every CONTROL_INTERVAL_MS
 *  - Turns the heater ON/OFF using a hysteresis band around SETPOINT_C
 *  - Enforces minimum ON/OFF times to avoid relay chatter
 *  - Optionally turns a fan ON/OFF if the room overheats
 */
void taskControlRelay()
{
    // === Non-blocking timer guard ===
    static uint32_t lastMs = 0;    // remembers last time this task ran
    const uint32_t now = millis(); // current time in ms
    if (now - lastMs < CONTROL_INTERVAL_MS)
        return;   // not time yet, exit quickly
    lastMs = now; // update timestamp

    // === Sanity check: skip if temperature is not valid ===
    if (isnan(gCurrentTemperature))
        return;

    // === Define hysteresis thresholds ===
    // The heater will turn ON when temperature <= lowThresh
    // and turn OFF when temperature >= highThresh.
    const float lowThresh = SETPOINT_C - HYSTERESIS_C;  // lower bound (heater ON)
    const float highThresh = SETPOINT_C + HYSTERESIS_C; // upper bound (heater OFF)

    // -------------------------------------------------------------------------
    //                        HEATER CONTROL LOGIC
    // -------------------------------------------------------------------------

    // If the heater is currently OFF, decide whether to turn it ON
    if (!gHeaterOn)
    {
        // Only turn ON if:
        // 1) Temperature is below the lower threshold, AND
        // 2) The heater has been OFF for at least MIN_OFF_MS
        if (gCurrentTemperature <= lowThresh && (now - gLastHeaterToggleMs >= MIN_OFF_MS))
        {
            gHeaterOn = true;                 // update state
            relayWrite(PIN_RELAY_HEAT, true); // activate relay
            gLastHeaterToggleMs = now;        // mark toggle time
        }
    }
    // If the heater is currently ON, decide whether to turn it OFF
    else
    {
        // Only turn OFF if:
        // 1) Temperature is above the upper threshold, AND
        // 2) The heater has been ON for at least MIN_ON_MS
        if (gCurrentTemperature >= highThresh && (now - gLastHeaterToggleMs >= MIN_ON_MS))
        {
            gHeaterOn = false;                 // update state
            relayWrite(PIN_RELAY_HEAT, false); // deactivate relay
            gLastHeaterToggleMs = now;         // mark toggle time
        }
    }

    // -------------------------------------------------------------------------
    //                        FAN CONTROL LOGIC (optional)
    // -------------------------------------------------------------------------
    // The fan only activates if the room is hotter than normal.
    // It turns ON at +2°C above setpoint and turns OFF at +1°C.
    // This creates a cooling band and prevents rapid toggling.

    const float fanOnThresh = SETPOINT_C + 2.0f;  // turn fan ON if >= this
    const float fanOffThresh = SETPOINT_C + 1.0f; // turn fan OFF if <= this

    // If the fan is currently OFF, decide whether to turn it ON
    if (!gFanOn)
    {
        // Only turn ON if temperature >= fanOnThresh and
        // the fan has been OFF for at least MIN_OFF_MS
        if (gCurrentTemperature >= fanOnThresh && (now - gLastFanToggleMs >= MIN_OFF_MS))
        {
            gFanOn = true;                   // update state
            relayWrite(PIN_RELAY_FAN, true); // activate relay
            gLastFanToggleMs = now;          // mark toggle time
        }
    }
    // If the fan is currently ON, decide whether to turn it OFF
    else
    {
        // Only turn OFF if temperature <= fanOffThresh and
        // the fan has been ON for at least MIN_ON_MS
        if (gCurrentTemperature <= fanOffThresh && (now - gLastFanToggleMs >= MIN_ON_MS))
        {
            gFanOn = false;                   // update state
            relayWrite(PIN_RELAY_FAN, false); // deactivate relay
            gLastFanToggleMs = now;           // mark toggle time
        }
    }
}
