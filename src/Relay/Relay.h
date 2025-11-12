#pragma once
#include <Arduino.h>
#include "Config.h"

inline void relayWrite(uint8_t pin, bool on)
{
    if (RELAY_ACTIVE_LOW)
    {
        digitalWrite(pin, on ? LOW : HIGH);
    }
    else
    {
        digitalWrite(pin, on ? HIGH : LOW);
    }
}
