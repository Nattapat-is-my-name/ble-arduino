#include <Arduino.h>
#include "wifi_setup.h"
#include "wifi_loop.h"

void setup()
{
  Serial.begin(115200);
  setupWiFi();
  setupBle();
}

void loop()
{
  handleSerialInput();
}
