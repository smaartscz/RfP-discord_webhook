#include "settings.h"
#include "mqtt/mqtt_topics.h"
Discord_Webhook discord;
AsyncWebServer server(80);
AsyncMqttClient mqttClient;

void setupWifi(){
    discord.begin(DISCORD_WEBHOOK);            // Inicializace discord webhooku
    discord.addWiFi(WiFi_ssid, WiFi_password); // Nastavení WiFi
    discord.connectWiFi();
    discord.send("🎶Ah, ha, ha, ha, stayin' alive, stayin' alive🎶, but if you're 555, I'm 666:love_you_gesture::fire:[.](https://tenor.com/view/666-digital-numbers-digital-numbers-flashing-gif-5944997)");
}

void RfP(unsigned long unixTime)
{
    time_t RfPDate;
    float fZbyva;
    int Zbyva;
    RfPDate = 1718186400L;                   // 12.6.2024
    fZbyva = (RfPDate - unixTime) / 86400.0; // Odecti momentalni unixTime od unix času RfP a vyděl to počtem sekund ve dni
    Zbyva = ceil(fZbyva);
    String message = "";
    switch (Zbyva)
    {
    case 300: // Kaja
        message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [**300**](https://media.discordapp.net/attachments/770062338564554798/954823564882739230/ezgif.com-gif-maker.gif) dní! (Přesněji za: <t:1718186400:R>):love_you_gesture::fire:";
        break;
    case 250: // Kaja2
        message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [**250**](https://cdn.discordapp.com/attachments/1064251020340899953/1125053321636483172/ezgif.com-video-to-gif_2.gif) dní! (Přesněji za: <t:1718186400:R>):love_you_gesture::fire: ";
        break;
    case 200: // BMTH
        message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [**200**](https://giphy.com/gifs/concert-bring-me-the-horizon-oliver-sykes-3sXu3d4qnRkI) dní! (Přesněji za: <t:1718186400:R>):love_you_gesture::fire:";
        break;
    case 150: // Corey Taylor
        message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [**150**](https://tenor.com/view/corey-taylor-skull-slasher-relax-gif-14853047) dní! (Přesněji za: <t:1718186400:R>):love_you_gesture::fire:";
        break;
    case 100: // PowerWolf
        message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [**100**](https://media.tenor.com/icraL6qB5pcAAAAC/powerwolf-fire-and-forgive.gif) dní! (Přesněji za: <t:1718186400:R>):love_you_gesture::fire:";
        break;
    case 50: // Electric Callboy
        message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [**50**](https://tenor.com/view/lets-do-it-again-fuck-yeah-electric-callboy-gif-26329254) dní! (Přesněji za: <t:1718186400:R>):love_you_gesture::fire:";
        break;
    case 31: // Crystal Lake
        message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [**31**](https://tenor.com/view/crystal-lake-apollo-music-video-gif-24063989) dní! (Přesněji za: <t:1718186400:R>):love_you_gesture::fire:";
        break;
    case 14: // Avril Lavigne
        message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za [**dva týdny**](https://tenor.com/view/avril-lavigne-%EC%97%90%EC%9D%B4%EB%B8%8C%EB%A6%B4-%EB%9D%BC%EB%B9%88-gif-7558323830048710247) týdny! (Přesněji za: <t:1718186400:R>):love_you_gesture::fire:";
        break;
    case 7: // Coldrain
        message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za **týden** https://media1.tenor.com/m/e_vIH7pm_DAAAAAd/one-ok-rock-35xxxv-doc.gif! (Přesněji za: <t:1718186400:R>):love_you_gesture::fire:";
        break;
    case 4: //Gutalax
        message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za **4** dny! (Přesněji za: <t:1718186400:R>):love_you_gesture::fire: [.](https://media1.tenor.com/m/WjmHMzsl2DEAAAAd/toi-toi-gutalax.gif)";
        break;
    case 3: // Slipknot
        message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za **3** dny! (Přesněji za: <t:1718186400:R>):love_you_gesture::fire: [.](https://media.tenor.com/aBAuw7ALCBEAAAAC/slipknot-duality.gif)";
        break;
    case 2: // Rammstein
        message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za **2** dny! (Přesněji za: <t:1718186400:R>):love_you_gesture::fire: [.](https://media.tenor.com/LtXzSqzcK3MAAAAC/dovperestroika.gif)";
        break;
    case 1: // Architects
        message = "Dobré FUCKIN poledne, <@&1121821428111646864> je za **zííííííííítra**! (Přesněji za: <t:1718186400:R>):love_you_gesture::fire: [.](https://media.tenor.com/gUUkhAnr5hcAAAAC/tenside-tensidemusic.gif)";
        break;
    case 0: // Slipknot headbang
        message = "PRÁVĚ TO VŠECHNO ZAČÍNÁ, <@&1121821428111646864>! **ENJOY**:love_you_gesture::fire: ||Jo a za 5 minut začíná Gutalax <:Kappa:798869995030970409>||[.](https://media.tenor.com/BQo9mt76WsYAAAAC/slipknot-drums.gif)";
        break;
    default:
        message = "Dobré poledne, <@&1121821428111646864> je za ";
        message += Zbyva;
        message += " dní";
        message += " (Přesněji za: <t:1718186400:R>)";
        message += ":love_you_gesture::fire: ||A je čas na obídek <:standaJoke:803355181692485744>||";
        break;
    }
    discord.send(message); // Pošli zprávu na discord
}

void manualRfP(String userID, unsigned long unixTime)
{
  time_t zbyva, RfPDate;
  RfPDate = 1718272800L;        // 12.6.2024
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

void setupOTA()
{
    ArduinoOTA.setHostname("ESP32_RfP");
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

void handleConfigRequest(AsyncWebServerRequest *request)
{
  if (request->hasParam("reset"))
  {
  }
  // You can send a response back to the client if needed
  request->send(200, "text/plain", "Request received");
}

void handleRfPRequest(AsyncWebServerRequest *request);

void handleRequest(AsyncWebServerRequest *request){
  // You can send a response back to the client if needed
  request->send(404, "text/plain", "Not found!");
}

void setupWebServer(){
      WebSerial.begin(&server);

  /* Attach Message Callback */
  WebSerial.msgCallback(recvMsg);

    server.begin();
  server.on("/rfp", HTTP_GET, [](AsyncWebServerRequest *request)
            { handleRfPRequest(request); });
  server.on("/config", HTTP_GET, [](AsyncWebServerRequest *request)
            { handleConfigRequest(request); }); 
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { handleRequest(request); });                   
  WebSerial.println("Server started");
}

void onMqttConnect(bool sessionPresent) {
  Serial.println("Connected to MQTT.");
  Serial.print("Session present: ");
  Serial.println(sessionPresent);
  uint16_t packetIdSub = mqttClient.subscribe("RfP/status", 2);
  uint16_t packetIdSub1 = mqttClient.subscribe("RfP/crrTime", 2);
  uint16_t packetIdSub2 = mqttClient.subscribe("RfP/unixTime", 2);
  mqttClient.publish("homeassistant/sensor/RfP/currTime/config", 0, true, currTime_auto);
  mqttClient.publish("homeassistant/sensor/RfP/unixTime/config", 0, true, unixTime_auto);
}

void connectToMqtt() {
  Serial.println("Connecting to MQTT...");
  mqttClient.connect();
}

void onMqttDisconnect(AsyncMqttClientDisconnectReason reason) {
  Serial.println("Disconnected from MQTT.");
  doOnce = false;
  if (reason == AsyncMqttClientDisconnectReason::TLS_BAD_FINGERPRINT) {
    Serial.println("Bad server fingerprint.");
  }

  if (WiFi.isConnected() && doOnce == false) {
    connectToMqtt();
    doOnce = true;
  }
}

void onMqttPublish(uint16_t packetId) {
  Serial.println("Publish acknowledged.");
  Serial.print("  packetId: ");
  Serial.println(packetId);
}

void setupMQTT(){
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(mqtt_server, mqtt_port);
  mqttClient.setCredentials(mqtt_user, mqtt_password);
  mqttClient.connect();
}

void sendTime(String currTime, unsigned long unixTime){
  String sunixTime = String(unixTime);
  const char *cunixTime =sunixTime.c_str();
  const char *ccurrTime =currTime.c_str();
  mqttClient.publish("RfP/currTime", 0, true, ccurrTime);
  mqttClient.publish("RfP/unixTime", 0, true, cunixTime);
}