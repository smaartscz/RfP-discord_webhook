//------------------Knihovny------------------------------------//
#include <WiFi.h>
#include <Discord_WebHook.h>
#include <Arduino.h>
#include <ArduinoOTA.h>
#include <WiFiClient.h>
#include <WebSerial.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <AsyncMqttClient.h>

#define my_hostname "ESP32_RfP"
#define sw_version "2023.11.27"

String DISCORD_WEBHOOK = "YOUR_DISCORD_WEBHOOK"; 
const char* WiFi_ssid = "YOUR_WIFI_SSID";
const char* WiFi_password = "YOUR_BEAUTIFUL_PASSWORD";


const char *ntpServer = "pool.ntp.org";
const int daylightOffset_sec = 3600;
const int gmtOffset_sec = 3600;

unsigned long lastSyncTime = 0;
const unsigned long syncInterval = 60;  // Sync every one minute

const char* mqtt_server = "YOUR_MQTT_SERVER_IP";
const char* mqtt_user = "YOUR_MQTT_USERNAME";
const char* mqtt_password = "YOUR_MQTT_PASSWORD";
#define mqtt_port 1883