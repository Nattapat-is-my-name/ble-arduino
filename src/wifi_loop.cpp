#include <Arduino.h>
#include "credentials.h"
#include "wifi_loop.h"
#include <WiFi.h>

void handleSerialInput()
{
    if (Serial.available())
    {
        String input = Serial.readStringUntil('\n');
        input.trim();

        if (input.equalsIgnoreCase("RESTART") || input.equalsIgnoreCase("r"))
        {
            Serial.println("Restarting...");
            ESP.restart();
        }

        if (input.equalsIgnoreCase("CLEAR") || input.equalsIgnoreCase("c"))
        {
            clearCredentials();
            Serial.println("Credentials cleared. Restarting...");
            ESP.restart();
        }
        else
        {
            int separatorIndex = input.indexOf(',');
            if (separatorIndex != -1)
            {
                String ssidStr = input.substring(0, separatorIndex);
                String passwordStr = input.substring(separatorIndex + 1);

                if (ssidStr.length() <= MAX_SSID_LENGTH && passwordStr.length() <= MAX_PASSWORD_LENGTH)
                {
                    saveCredentials(ssidStr.c_str(), passwordStr.c_str());

                    Serial.println("Credentials saved. Restarting...");
                    ESP.restart();
                }
                else
                {
                    Serial.println("SSID or password too long.");
                }
            }
            else
            {
                Serial.println("Invalid format. Use: SSID,PASSWORD");
            }
        }
    }
}
