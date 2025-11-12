// src/main.cpp  (PlatformIO) or main.cpp in your project
#include <Arduino.h>

#include "Config.h"
#include "Shared/Devices.h"
#include "Shared/State.h"
#include "Relay/Relay.h"

#include "Sensors/TaskReadSensors.h"
#include "LCD/TaskUpdateLcd.h"
#include "Serial/TaskLogSerial.h"
#include "Relay/TaskControlRelay.h"

void setup()
{
  initSerial();
  initDht();
  initLcd();
  printSensorDetails();
  initRelays();
}

void loop()
{
  // Each task owns its own millis() timer internally
  taskReadSensors();
  taskUpdateLcd();
  taskLogSerial();
  taskControlRelay();

  // Add more task* calls here if you create new modules.
}
