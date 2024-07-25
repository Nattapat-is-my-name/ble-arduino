#ifndef CREDENTIALS_H
#define CREDENTIALS_H

#include <Arduino.h>

// Maximum length for SSID and Password
#define MAX_SSID_LENGTH 32
#define MAX_PASSWORD_LENGTH 64

// Define EEPROM addresses
#define SSID_ADDRESS 0
#define PASSWORD_ADDRESS (SSID_ADDRESS + MAX_SSID_LENGTH)

struct Credentials
{
    char ssid[MAX_SSID_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

struct WiFiDetails
{
    char ssid[MAX_SSID_LENGTH];
    IPAddress ip;
    int channel;
    int32_t rssi;
    String hostname;
    String macAddress;
};

void readCredentials(char *ssid, char *password);
void saveCredentials(const char *ssid, const char *password);
void clearCredentials();
void restartWiFi();
WiFiDetails connectToWiFi(const char *ssid, const char *password);

#endif
