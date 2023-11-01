/*


Rock For People Discord countdown



*/

//------------------Knihovny------------------------------------//
#include <WiFi.h>
#include <Discord_WebHook.h>
#include "settings.h"
#include <ArduinoOTA.h>
#include <WiFiClient.h>
#include "rfp.h"
#include <WebSerial.h>
//------------------Základní konfigurace------------------------//
Discord_Webhook discord;
const char *ntpServer = "cz.pool.ntp.org";
const long gmtOffset_sec = 0;
const int daylightOffset_sec = 3600;
int hour_old;
bool doOnce = false;
unsigned long unixTime;

AsyncWebServer server(80);

// Získej UNIX čas
unsigned long getTime()
{
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    return (0);
  }
  time(&now);
  return now;
}

void manualRfP(String userId);

void handleRequest(AsyncWebServerRequest *request){
  if (request->hasParam("id"))
  {
    String id = request->getParam("id")->value();
    manualRfP(id);
  }
  if (request->hasParam("reset"))
  {
    doOnce = false;
    hour_old = 0;
  }
  // You can send a response back to the client if needed
  request->send(200, "text/plain", "Request received");
}

void setupServer()
{
  server.begin();
  server.on("/rfp", HTTP_GET, [](AsyncWebServerRequest *request)
            { handleRequest(request); });
  WebSerial.println("Server started");
}

void recvMsg(uint8_t *data, size_t len)
{
  WebSerial.println("Received Data...");
  String d = "";
  for (int i = 0; i < len; i++)
  {
    d += char(data[i]);
  }
  WebSerial.println(d);
}

// Inicializace WiFi, Discord webhooku a NTP času
void setup()
{
  Serial.begin(115200);
  discord.begin(DISCORD_WEBHOOK);                                                                                                                     // Inicializace discord webhooku
  discord.addWiFi(WiFi_ssid, WiFi_password);                                                                                                          // Nastavení WiFi
  discord.connectWiFi();                                                                                                                              // Připoj se k WiFi
  discord.send("If you're 555, I'm 666:love_you_gesture::fire:[.](https://tenor.com/view/666-digital-numbers-digital-numbers-flashing-gif-5944997)"); // Pošli zprávu o zapnutí
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);                                                                                           // Nastav NTP server
  time_t now;
  while ((now = time(nullptr)) == 0)
  {
    delay(1000);
    WebSerial.println("Čeká se na synchronizaci času...");
  }
  delay(2000);
  ArduinoOTA.setHostname("RfP-Webhook");
  ArduinoOTA
      .onStart([]()
               {
      String type;
      if (ArduinoOTA.getCommand() == U_FLASH)
        type = "sketch";
      else  // U_SPIFFS
        type = "filesystem";

      // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
      Serial.println("Start updating " + type); })
      .onEnd([]()
             { Serial.println("\nEnd"); })
      .onProgress([](unsigned int progress, unsigned int total)
                  { Serial.printf("Progress: %u%%\r", (progress / (total / 100))); })
      .onError([](ota_error_t error)
               {
      Serial.printf("Error[%u]: ", error);
      if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
      else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
      else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
      else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
      else if (error == OTA_END_ERROR) Serial.println("End Failed"); });
  ArduinoOTA.setPassword((const char *)"666");
  ArduinoOTA.begin();
  WebSerial.begin(&server);

  /* Attach Message Callback */
  WebSerial.msgCallback(recvMsg);
  setupServer();
}

// Funkce na posílání zprávy
void RfP()
{
  unixTime = getTime();
  time_t Zbyva, RfPDate;
  RfPDate = 1718272800L;                // 13.6.2024
  Zbyva = (RfPDate - unixTime) / 86400; // Odecti momentalni unixTime od unix času RfP a vyděl to počtem sekund ve dni
  String message = "";
  WebSerial.print(message);
  switch (Zbyva)
  {
  case 300: // Kaja
    message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [300](https://media.discordapp.net/attachments/770062338564554798/954823564882739230/ezgif.com-gif-maker.gif) dní!(<t:1718272800:R>):love_you_gesture::fire:";
    break;
  case 250: // Kaja2
    message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [250](https://cdn.discordapp.com/attachments/1064251020340899953/1125053321636483172/ezgif.com-video-to-gif_2.gif) dní!(<t:1718272800:R>):love_you_gesture::fire: ";
    break;
  case 200: // BMTH
    message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [200](https://giphy.com/gifs/concert-bring-me-the-horizon-oliver-sykes-3sXu3d4qnRkI) dní!(<t:1718272800:R>):love_you_gesture::fire:";
    break;
  case 150: // Architects
    message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [150](https://media.discordapp.net/attachments/1064251020340899953/1125052433144487936/ezgif.com-video-to-gif_1.gif) dní!(<t:1718272800:R>):love_you_gesture::fire:";
    break;
  case 100: // PowerWolf
    message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [100](https://media.tenor.com/icraL6qB5pcAAAAC/powerwolf-fire-and-forgive.gif) dní!(<t:1718272800:R>):love_you_gesture::fire:";
    break;
  case 50: // Electric Callboy
    message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [50](https://tenor.com/view/lets-do-it-again-fuck-yeah-electric-callboy-gif-26329254) dní!(<t:1718272800:R>):love_you_gesture::fire:";
    break;
  case 31: // Linkin Park
    message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [31](https://media.tenor.com/6SEu35ns1pwAAAAC/linkin-park.gif) dní!(<t:1718272800:R>):love_you_gesture::fire:";
    break;
  case 14: // Moshpit
    message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [dva](https://media.tenor.com/rObe8p1aJgUAAAAC/slam-head-banger.gif) týdny!(<t:1718272800:R>):love_you_gesture::fire:";
    break;
  case 7: // RFP 2023
    message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [týden](https://cdn.discordapp.com/attachments/1064251020340899953/1125051885703929876/ezgif.com-video-to-gif.gif)!(<t:1718272800:R>):love_you_gesture::fire:";
    break;
  case 3: // Slipknot
    message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [3](https://media.tenor.com/aBAuw7ALCBEAAAAC/slipknot-duality.gif) dny!(<t:1718272800:R>):love_you_gesture::fire:";
    break;
  case 2: // Rammstein
    message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [2](https://media.tenor.com/LtXzSqzcK3MAAAAC/dovperestroika.gif) dny!(<t:1718272800:R>):love_you_gesture::fire:";
    break;
  case 1: // Architects
    message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [zííííííííítra](https://media.tenor.com/gUUkhAnr5hcAAAAC/tenside-tensidemusic.gif)!(<t:1718272800:R>):love_you_gesture::fire:";
    break;
  case 0: // Slipknot headbang
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
  discord.send(message); // Pošli zprávu na discord
}

void manualRfP(String userID)
{
  unixTime = getTime();
  time_t zbyva, RfPDate;
  RfPDate = 1718272800L;        // 13.6.2024
  zbyva = (RfPDate - unixTime); // Odecti momentalni unixTime od unix času RfP
  // Vypocitej zbyvajici dny, hodiny a minuty
  unsigned long days = zbyva / (24 * 60 * 60);
  unsigned long remaining_seconds = zbyva % (24 * 60 * 60);
  unsigned long hours = remaining_seconds / (60 * 60);
  unsigned long remaining_minutes = (remaining_seconds % (60 * 60)) / 60;
  unsigned long minutes = remaining_minutes % 60;
  String message = "Čau <@" + userID + ">, Rock for people je za " + days + " dní, " + hours + " hodin a " + minutes + " minut:love_you_gesture::fire:";
  discord.send(message); // Pošli zprávu na discord
}
void sendTime(int currTime)
{
  if (currTime != hour_old)
  {
    String msg = "Právě je: ";
    hour_old = currTime;
    msg += currTime;
    msg += " hodin";
    WebSerial.println(msg);
  }
}
void onStartup()
{
  if (doOnce == false){
    delay(1000);
    WebSerial.print(F("IP address: "));
    WebSerial.println(WiFi.localIP());
    WebSerial.printf("Millis=%lu\n", millis());
    WebSerial.printf("Free heap=[%u]\n", ESP.getFreeHeap());
    doOnce = true;
  }
}
void loop(){
  onStartup();
  struct tm timeinfo;    
  if (!getLocalTime(&timeinfo))
  {
    WebSerial.println("Nelze získat aktuální čas");
    return;
  }
  sendTime(timeinfo.tm_hour);
  RfP_check();
  ArduinoOTA.handle();
}