/*
Rock For People Discord countdown
*/

//------------------Knihovny------------------------------------//
#include <WiFi.h>
#include <Discord_WebHook.h>
#include "time.h"
#include "settings.h"

//------------------Základní konfigurace------------------------//
Discord_Webhook discord;
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;
unsigned long unixTime;


//Získej UNIX čas
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return (0);
  }
  time(&now);
  return now;
}

//Inicializace WiFi, Discord webhooku a NTP času
void setup() {
  Serial.begin(115200);
  discord.begin(DISCORD_WEBHOOK);                                  // Inicializace discord webhooku
  discord.addWiFi(WiFi_ssid, WiFi_password);                       // Nastavení WiFi
  discord.connectWiFi();                                           // Připoj se k WiFi
  discord.send("If you're 555, I'm 666:love_you_gesture::fire:");  // Pošli zprávu o zapnutí
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);        //Nastav NTP server
  time_t now;
  while ((now = time(nullptr)) == 0) {
    delay(1000);
    Serial.println("Čeká se na synchronizaci času...");
  }
  delay(2000);
  //setupTimer();
}


//Funkce na posílání zprávy
void RfP() {
  unixTime = getTime();
  time_t Zbyva, RfPDate;
  RfPDate = 1718272800L;                 // 13.6.2024
  Zbyva = (RfPDate - unixTime) / 86400;  // Odecti momentalni unixTime od unix času RfP a vyděl to počtem sekund ve dni
  String message = "Dobré poledne, <@&1121821428111646864> je za ";
  message += Zbyva;
  message += " dní";
  message += "(<t:1718272800:R>)";
  message += ":love_you_gesture::fire:";
  Serial.print(message);
  discord.send(message);  //Pošli zprávu na discord
}


void loop() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Nelze získat aktuální čas");
    return;
  }
  if (timeinfo.tm_hour == 12 && timeinfo.tm_min == 00 && timeinfo.tm_sec == 0) {
    RfP(); //Trigger RfP funkci
  }
}