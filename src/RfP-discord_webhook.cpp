/*


Rock For People Discord countdown



*/

//------------------Knihovny------------------------------------//
#include <WiFi.h>
#include <Discord_WebHook.h>
#include "time.h"
#include "settings.h"
#include <ArduinoOTA.h>
#include <WiFiClient.h>
#include <WebServer.h>
//------------------Základní konfigurace------------------------//
Discord_Webhook discord;
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 3600;
const int daylightOffset_sec = 3600;
unsigned long unixTime;
WebServer server(80);

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

void manualRfP(String userId);

void handleRequest() {
  if (server.hasArg("id")) {
    String id = server.arg("id");
    manualRfP(id);
  }

  // You can send a response back to the client if needed
  server.send(200, "text/plain", "RfP request received");
}


void setupServer() {
  server.on("/rfp", HTTP_GET, handleRequest);
  server.begin();
  Serial.println("Server started");
}

//Inicializace WiFi, Discord webhooku a NTP času
void setup() {
  Serial.begin(115200);
  discord.begin(DISCORD_WEBHOOK);             // Inicializace discord webhooku
  discord.addWiFi(WiFi_ssid, WiFi_password);  // Nastavení WiFi
  discord.connectWiFi();                      // Připoj se k WiFi
  discord.send("If you're 555, I'm 666:love_you_gesture::fire:[.](https://tenor.com/view/666-digital-numbers-digital-numbers-flashing-gif-5944997)");  // Pošli zprávu o zapnutí
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);  //Nastav NTP server
  time_t now;
  while ((now = time(nullptr)) == 0) {
    delay(1000);
    Serial.println("Čeká se na synchronizaci času...");
  }
  delay(2000);
  ArduinoOTA.setHostname("RfP-Webhook");
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
  ArduinoOTA.setPassword((const char*)"666");
  ArduinoOTA.begin();
  setupServer();
}


//Funkce na posílání zprávy
void RfP() {
  unixTime = getTime();
  time_t Zbyva, RfPDate;
  RfPDate = 1718272800L;                 // 13.6.2024
  Zbyva = (RfPDate - unixTime) / 86400;  // Odecti momentalni unixTime od unix času RfP a vyděl to počtem sekund ve dni
  String message = "";
  Serial.print(message);
  switch (Zbyva) {
    case 300:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [300](https://media.discordapp.net/attachments/770062338564554798/954823564882739230/ezgif.com-gif-maker.gif) dní!(<t:1718272800:R>):love_you_gesture::fire:";
      break;
    case 250:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [250](https://cdn.discordapp.com/attachments/1064251020340899953/1125053321636483172/ezgif.com-video-to-gif_2.gif) dní!(<t:1718272800:R>):love_you_gesture::fire: ";
      break;
    case 200:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [200](https://media.discordapp.net/attachments/1064251020340899953/1125052433144487936/ezgif.com-video-to-gif_1.gif) dní!(<t:1718272800:R>):love_you_gesture::fire:";
      break;
    case 150:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [150](https://media.discordapp.net/attachments/1064251020340899953/1125052433144487936/ezgif.com-video-to-gif_1.gif) dní!(<t:1718272800:R>):love_you_gesture::fire:";
      break;
    case 100:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [100](https://media.tenor.com/icraL6qB5pcAAAAC/powerwolf-fire-and-forgive.gif) dní!(<t:1718272800:R>):love_you_gesture::fire:";
      break;
    case 50:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [50](https://tenor.com/view/lets-do-it-again-fuck-yeah-electric-callboy-gif-26329254) dní!(<t:1718272800:R>):love_you_gesture::fire:";
      break;
    case 31:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [31](https://media.tenor.com/6SEu35ns1pwAAAAC/linkin-park.gif) dní!(<t:1718272800:R>):love_you_gesture::fire:";
      break;
    case 14:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [dva](https://media.tenor.com/rObe8p1aJgUAAAAC/slam-head-banger.gif) týdny!(<t:1718272800:R>):love_you_gesture::fire:";
      break;
    case 7:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [týden](https://cdn.discordapp.com/attachments/1064251020340899953/1125051885703929876/ezgif.com-video-to-gif.gif)!(<t:1718272800:R>):love_you_gesture::fire:";
      break;
    case 3:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [3](https://media.tenor.com/aBAuw7ALCBEAAAAC/slipknot-duality.gif) dny!(<t:1718272800:R>):love_you_gesture::fire:";
      break;
    case 2:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [2](https://media.tenor.com/LtXzSqzcK3MAAAAC/dovperestroika.gif) dny!(<t:1718272800:R>):love_you_gesture::fire:";
      break;
    case 1:
      message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [zííííííííítra](https://media.tenor.com/gUUkhAnr5hcAAAAC/tenside-tensidemusic.gif)!(<t:1718272800:R>):love_you_gesture::fire:";
      break;
    case 0:
      message = "PRÁVĚ TO VŠECHNO ZAČÍNÁ, <@&1121821428111646864>! [ENJOY](https://media.tenor.com/BQo9mt76WsYAAAAC/slipknot-drums.gif):love_you_gesture::fire:";
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

void manualRfP(String userID) {
  unixTime = getTime();
  time_t Zbyva, RfPDate;
  RfPDate = 1718272800L;                 // 13.6.2024
  Zbyva = (RfPDate - unixTime) / 86400;  // Odecti momentalni unixTime od unix času RfP a vyděl to počtem sekund ve dni
  String message = "Čau <@";
  message += userID;
  message += ">, Rock for people je za ";
  message += Zbyva;
  message += " dní(<t:1718272800:R>)";
  message += ":love_you_gesture::fire:";
  discord.send(message);  //Pošli zprávu na discord
}

void loop() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Nelze získat aktuální čas");
    return;
  }
  if (timeinfo.tm_hour == 12 && timeinfo.tm_min == 00 && timeinfo.tm_sec == 0) {
    RfP();  //Trigger RfP funkci
  }
  ArduinoOTA.handle();
  server.handleClient();
}
