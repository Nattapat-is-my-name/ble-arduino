#include <EEPROM.h>
#include <WiFi.h>
#include "credentials.h"

void readCredentials(char *ssid, char *password)
{
    EEPROM.begin(512);

    // Read SSID
    for (int i = 0; i < MAX_SSID_LENGTH; i++)
    {
        ssid[i] = EEPROM.read(SSID_ADDRESS + i);
        if (ssid[i] == '\0')
            break;
    }

    // Read Password
    for (int i = 0; i < MAX_PASSWORD_LENGTH; i++)
    {
        password[i] = EEPROM.read(PASSWORD_ADDRESS + i);
        if (password[i] == '\0')
            break;
    }
}

void saveCredentials(const char *ssid, const char *password)
{
    EEPROM.begin(512);

    // Save SSID
    for (int i = 0; i < MAX_SSID_LENGTH; i++)
    {
        EEPROM.write(SSID_ADDRESS + i, i < strlen(ssid) ? ssid[i] : '\0');
    }

    // Save Password
    for (int i = 0; i < MAX_PASSWORD_LENGTH; i++)
    {
        EEPROM.write(PASSWORD_ADDRESS + i, i < strlen(password) ? password[i] : '\0');
    }

    EEPROM.commit();
}

void clearCredentials()
{
    EEPROM.begin(512);

    // Clear SSID
    for (int i = 0; i < MAX_SSID_LENGTH; i++)
    {
        EEPROM.write(SSID_ADDRESS + i, '\0');
    }

    // Clear Password
    for (int i = 0; i < MAX_PASSWORD_LENGTH; i++)
    {
        EEPROM.write(PASSWORD_ADDRESS + i, '\0');
    }

    EEPROM.commit();
}

void restartWiFi()
{
    Serial.println("Restarting...");
    ESP.restart();
}

WiFiDetails connectToWiFi(const char *ssid, const char *password)
{
    WiFiDetails details;
    strncpy(details.ssid, ssid, MAX_SSID_LENGTH);
    WiFi.begin(ssid, password);
    int attempt = 0;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
        if (++attempt == 20)
        {
            Serial.println("Connection failed.");
            return details;
        }
    }

    Serial.println();
    Serial.print("Connected! IP address: ");
    details.ip = WiFi.localIP();
    Serial.println(details.ip);
    details.channel = WiFi.channel();
    details.rssi = WiFi.RSSI();
    details.hostname = WiFi.getHostname();
    details.macAddress = WiFi.macAddress();
    Serial.print("Channel: ");
    Serial.println(details.channel);
    Serial.print("RSSI: ");
    Serial.println(details.rssi);
    Serial.print("Hostname: ");
    Serial.println(details.hostname);
    Serial.print("MAC Address: ");
    Serial.println(details.macAddress);

    return details;
}