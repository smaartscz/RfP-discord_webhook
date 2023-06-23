/*
Rock For People Discord countdown
*/

//Knihovny
#include <WiFi.h>
#include <Discord_WebHook.h>
#include "time.h"
#include <CronAlarms.h>
#include "settings.h"
//Základní config
Discord_Webhook discord;
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;
unsigned long unixTime;

CronId id;

//Vypiš čas do seriové linky
void printLocalTime() {
  struct tm timeinfo;
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

//Získej UNIX čas
unsigned long getTime() {
  time_t now;
  struct tm timeinfo;
  time(&now);
  return now;
}

//Inicializace WiFi, Discord webhooku a vytvoření Cron události
void setup() {
  Serial.begin(115200);
  discord.begin(DISCORD_WEBHOOK);             // Inicializace discord webhooku
  discord.addWiFi(WiFi_ssid, WiFi_password);  // Nastavení WiFi
  discord.connectWiFi();                      // Připoj se k WiFi
  discord.send("If you're 555, I'm 666:love_you_gesture::fire:"); // Pošli zprávu o zapnutí
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);  //Nastav NTP server
  printLocalTime();
  Cron.create("0 0 10 ? * * *", RfP, false);  //Každý den v 10h zavolej funkci RfP
}

//Funkce na posílání zprávy
void RfP() {
  unixTime = getTime();
  time_t Zbyva, RfPDate;
  RfPDate = 1718272800L;                 // 13.6.2024
  Zbyva = (RfPDate - unixTime) / 86400;  // Odecti momentalni unixTime od unix času RfP a vyděl to počtem sekund ve dni
  String message = "Dobré ráno, <@&1121821428111646864> je za ";
  message += Zbyva;
  message += " dní";
  message += "(<t:1718272800:R>)";
  message += ":love_you_gesture::fire:";
  discord.send(message);  //Pošli zprávu na discord
}


void loop() {
  Cron.delay(1000);
  printLocalTime();  //Zavolej funkci printLocalTime()
}