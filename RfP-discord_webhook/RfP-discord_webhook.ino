/*


Rock For People Discord countdown



*/

//------------------Knihovny------------------------------------//
#include <WiFi.h>
#include <Discord_WebHook.h>
#include "time.h"
#include "functions.h"
#include <ArduinoOTA.h>
//------------------Základní konfigurace------------------------//

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
  discord.begin(DISCORD_WEBHOOK);             // Inicializace discord webhooku
  discord.addWiFi(WiFi_ssid, WiFi_password);  // Nastavení WiFi
  discord.connectWiFi();                      // Připoj se k WiFi
  discord.send("If you're 555, I'm 666:love_you_gesture::fire:");  // Pošli zprávu o zapnutí
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);  //Nastav NTP server
  time_t now;
  while ((now = time(nullptr)) == 0) {
    delay(1000);
    Serial.println("Čeká se na synchronizaci času...");
  }
  delay(2000);
  ArduinoOTA.setHostname("RfP Webhook");
  ArduinoOTA
    .onStart([]() {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else  // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type);
    })
    .onEnd([]() {
      Serial.println("\nEnd");
    })
    .onProgress([](unsigned int progress, unsigned int total) {
      Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    })
    .onError([](ota_error_t error) {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed");
    });

  ArduinoOTA.begin();
}


//Funkce na posílání zprávy
void RfP() {
  unixTime = getTime();
  time_t Zbyva, RfPDate;
  RfPDate = 1718272800L;                 // 13.6.2024
  Zbyva = (RfPDate - unixTime) / 86400;  // Odecti momentalni unixTime od unix času RfP a vyděl to počtem sekund ve dni
  Zbyva = 50;
  String message = "";
  Serial.print(message);
  switch (Zbyva) {
    case 300:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za 300 dní!(<t:1718272800:R>):love_you_gesture::fire: https://rfp.smaarts.cz/300";
      break;
    case 250:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za 250 dní!(<t:1718272800:R>):love_you_gesture::fire: https://rfp.smaarts.cz/250";
      break;
    case 200:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za 200 dní!(<t:1718272800:R>):love_you_gesture::fire: https://rfp.smaarts.cz/200";
      break;
    case 150:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za 150 dní!(<t:1718272800:R>):love_you_gesture::fire: https://rfp.smaarts.cz/150";
      break;
    case 100:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za 100 dní!(<t:1718272800:R>):love_you_gesture::fire: https://rfp.smaarts.cz/100";
      break;
    case 50:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za 50 dní!(<t:1718272800:R>):love_you_gesture::fire: https://rfp.smaarts.cz/50";
      break;
    case 31:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za 31 dní!(<t:1718272800:R>):love_you_gesture::fire: https://rfp.smaarts.cz/31";
      break;
    case 14:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za dva týdny!(<t:1718272800:R>):love_you_gesture::fire: https://rfp.smaarts.cz/14";
      break;
    case 7:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za týden!(<t:1718272800:R>):love_you_gesture::fire: https://rfp.smaarts.cz/7";
      break;
    case 3:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za 3 dny!(<t:1718272800:R>):love_you_gesture::fire: https://rfp.smaarts.cz/3";
      break;
    case 2:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za 2 dny!(<t:1718272800:R>):love_you_gesture::fire: https://rfp.smaarts.cz/2";
      break;
    case 1:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za zííííííííítra!(<t:1718272800:R>):love_you_gesture::fire: https://rfp.smaarts.cz/1";
      break;
    case 0:
      message = "PRÁVĚ TO VŠECHNO ZAČÍNÁ, <@&1121821428111646864>! ENJOY:love_you_gesture::fire: https://rfp.smaarts.cz/dnes";
      break;
    default:
      message = "Dobré poledne, <@&1121821428111646864> je za ";
      message += Zbyva;
      message += " dní";
      message += "(<t:1718272800:R>)";
      message += ":love_you_gesture::fire:";
      break;
  }
  discord.send(message);  //Pošli zprávu na discord
}


void loop() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Nelze získat aktuální čas");
    return;
  }
  if (timeinfo.tm_hour == 13 && timeinfo.tm_min == 25 && timeinfo.tm_sec == 0) {
    RfP();  //Trigger RfP funkci
  }
  ArduinoOTA.handle();
  //RfP();
}
