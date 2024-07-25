#include <Arduino.h>
#include "credentials.h"
#include "wifi_setup.h"
#include <WiFi.h>

void setupWiFi()
{
    char ssid[MAX_SSID_LENGTH] = {0};
    char password[MAX_PASSWORD_LENGTH] = {0};

    readCredentials(ssid, password);

    if (ssid[0] != '\0' && password[0] != '\0')
    {
        Serial.print("Connecting to ");
        Serial.println(ssid);
        connectToWiFi(ssid, password);
    }
    else
    {
        Serial.println("No saved credentials.");
    }
}
