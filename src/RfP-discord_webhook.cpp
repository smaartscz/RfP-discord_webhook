/*


Rock For People Discord countdown



*/
#include "functions.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, ntpServer, gmtOffset_sec, daylightOffset_sec);

void syncTime() {
  Serial.println("Syncing time...");
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  time_t now = time(nullptr);
  while (now < 10000) {
    delay(1000);
    Serial.println("Waiting for NTP time sync...");
    now = time(nullptr);
  }

  Serial.println("Time synced successfully");
  Serial.println("Current time: ");
  Serial.println(timeClient.getEpochTime());
  String currTime = String(timeClient.getHours()) + String(timeClient.getMinutes());
  sendTime(currTime, timeClient.getEpochTime());
}

void handleRfPRequest(AsyncWebServerRequest *request)
{
  if (request->hasParam("id"))
  {
    String id = request->getParam("id")->value();
    timeClient.update();
    manualRfP(id, timeClient.getEpochTime());
    request->send(200, "text/plain", "Request received");
  }
  // You can send a response back to the client if needed
  request->send(200, "text/plain", "Request received");
}

void setup() {    
  Serial.begin(115200);
  setupWifi();
  syncTime();
  setupOTA();
  setupWebServer();
  setupMQTT();
}

void loop() {
timeClient.update();
  // Check if it's time to run the function at 12 pm (12:00:00)
  if (timeClient.getHours() == 12 && timeClient.getMinutes() == 00 && sentRfP == false) {
    RfP(timeClient.getEpochTime());  // Call your function
    sentRfP = true;
    delay(1000);  // Avoid repeated calls during the same second

  }
if (timeClient.getHours() == 12 && timeClient.getMinutes() >= 01 && sentRfP == true) {
  sentRfP = false;
  }
  // Check if it's time to sync with NTP server
  if (currentTime - lastSyncTime >= syncInterval) {
    syncTime();
    lastSyncTime = currentTime;
  }
  ArduinoOTA.handle();
}