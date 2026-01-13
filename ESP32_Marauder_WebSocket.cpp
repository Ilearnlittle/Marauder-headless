#include "ESP32_Marauder_Headless.h"

extern AsyncWebSocket ws;
extern bool isRunning;
extern String currentOperation;
extern int connectedClients;
extern DeauthController deauthController;
extern BeaconSpam beaconSpam;
extern ProbeCapture probeCapture;
extern PacketMonitor packetMonitor;
extern HandshakeCapture handshakeCapture;
extern EvilTwin evilTwin;
extern DNSServer dnsServer;
extern Settings settings;

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    String message = (char*)data;
    
    // Parse JSON command
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, message);
    
    if (error) {
      Serial.print("deserializeJson() failed: ");
      Serial.println(error.f_str());
      return;
    }
    
    String action = doc["action"];
    
    if (action == "getStatus") {
      sendStatusUpdate();
    }
    else if (action == "startDeauth") {
      String target = doc["target"];
      String mode = doc["mode"];
      int packets = doc["packets"];
      bool continuous = doc["continuous"];
      
      currentOperation = "deauth";
      isRunning = true;
      deauthController.start(target, mode, packets, continuous);
      
      // Notify clients
      DynamicJsonDocument responseDoc(256);
      responseDoc["type"] = "status";
      responseDoc["operation"] = currentOperation;
      responseDoc["running"] = isRunning;
      
      String response;
      serializeJson(responseDoc, response);
      ws.textAll(response);
    }
    else if (action == "stopDeauth") {
      deauthController.stop();
      isRunning = false;
      currentOperation = "none";
      
      // Notify clients
      DynamicJsonDocument responseDoc(256);
      responseDoc["type"] = "status";
      responseDoc["operation"] = currentOperation;
      responseDoc["running"] = isRunning;
      
      String response;
      serializeJson(responseDoc, response);
      ws.textAll(response);
    }
    else if (action == "startBeacon") {
      String mode = doc["mode"];
      int count = doc["count"];
      int interval = doc["interval"];
      String ssids = doc["ssids"];
      
      currentOperation = "beacon";
      isRunning = true;
      beaconSpam.start(mode, count, interval, ssids);
      
      // Notify clients
      DynamicJsonDocument responseDoc(256);
      responseDoc["type"] = "status";
      responseDoc["operation"] = currentOperation;
      responseDoc["running"] = isRunning;
      
      String response;
      serializeJson(responseDoc, response);
      ws.textAll(response);
    }
    else if (action == "stopBeacon") {
      beaconSpam.stop();
      isRunning = false;
      currentOperation = "none";
      
      // Notify clients
      DynamicJsonDocument responseDoc(256);
      responseDoc["type"] = "status";
      responseDoc["operation"] = currentOperation;
      responseDoc["running"] = isRunning;
      
      String response;
      serializeJson(responseDoc, response);
      ws.textAll(response);
    }
    else if (action == "startEvilTwin") {
      String ssid = doc["ssid"];
      int channel = doc["channel"];
      bool captivePortal = doc["captivePortal"];
      String portalType = doc["portalType"];
      
      currentOperation = "evilTwin";
      isRunning = true;
      evilTwin.start(ssid, channel, captivePortal, portalType);
      
      // Start DNS server for captive portal if needed
      if (captivePortal) {
        dnsServer.start(DNS_PORT, "*", WiFi.softAPIP());
      }
      
      // Notify clients
      DynamicJsonDocument responseDoc(256);
      responseDoc["type"] = "status";
      responseDoc["operation"] = currentOperation;
      responseDoc["running"] = isRunning;
      
      String response;
      serializeJson(responseDoc, response);
      ws.textAll(response);
    }
    else if (action == "stopEvilTwin") {
      evilTwin.stop();
      dnsServer.stop();
      isRunning = false;
      currentOperation = "none";
      
      // Notify clients
      DynamicJsonDocument responseDoc(256);
      responseDoc["type"] = "status";
      responseDoc["operation"] = currentOperation;
      responseDoc["running"] = isRunning;
      
      String response;
      serializeJson(responseDoc, response);
      ws.textAll(response);
    }
    else if (action == "startPacketMonitor") {
      int channel = doc["channel"];
      String filter = doc["filter"];
      bool savePcap = doc["savePcap"];
      
      currentOperation = "packet";
      isRunning = true;
      packetMonitor.start(channel, filter, savePcap);
      
      // Notify clients
      DynamicJsonDocument responseDoc(256);
      responseDoc["type"] = "status";
      responseDoc["operation"] = currentOperation;
      responseDoc["running"] = isRunning;
      
      String response;
      serializeJson(responseDoc, response);
      ws.textAll(response);
    }
    else if (action == "stopPacketMonitor") {
      packetMonitor.stop();
      isRunning = false;
      currentOperation = "none";
      
      // Notify clients
      DynamicJsonDocument responseDoc(256);
      responseDoc["type"] = "status";
      responseDoc["operation"] = currentOperation;
      responseDoc["running"] = isRunning;
      
      String response;
      serializeJson(responseDoc, response);
      ws.textAll(response);
    }
    else if (action == "startProbeMonitor") {
      bool hopping = doc["hopping"];
      int channel = doc["channel"];
      bool savePcap = doc["savePcap"];
      
      currentOperation = "probe";
      isRunning = true;
      probeCapture.start(hopping, channel, savePcap);
      
      // Notify clients
      DynamicJsonDocument responseDoc(256);
      responseDoc["type"] = "status";
      responseDoc["operation"] = currentOperation;
      responseDoc["running"] = isRunning;
      
      String response;
      serializeJson(responseDoc, response);
      ws.textAll(response);
    }
    else if (action == "stopProbeMonitor") {
      probeCapture.stop();
      isRunning = false;
      currentOperation = "none";
      
      // Notify clients
      DynamicJsonDocument responseDoc(256);
      responseDoc["type"] = "status";
      responseDoc["operation"] = currentOperation;
      responseDoc["running"] = isRunning;
      
      String response;
      serializeJson(responseDoc, response);
      ws.textAll(response);
    }
    else if (action == "startHandshake") {
      String ssid = doc["ssid"];
      int channel = doc["channel"];
      bool autoDeauth = doc["autoDeauth"];
      
      currentOperation = "handshake";
      isRunning = true;
      handshakeCapture.start(ssid, channel, autoDeauth);
      
      // Notify clients
      DynamicJsonDocument responseDoc(256);
      responseDoc["type"] = "status";
      responseDoc["operation"] = currentOperation;
      responseDoc["running"] = isRunning;
      
      String response;
      serializeJson(responseDoc, response);
      ws.textAll(response);
    }
    else if (action == "stopHandshake") {
      handshakeCapture.stop();
      isRunning = false;
      currentOperation = "none";
      
      // Notify clients
      DynamicJsonDocument responseDoc(256);
      responseDoc["type"] = "status";
      responseDoc["operation"] = currentOperation;
      responseDoc["running"] = isRunning;
      
      String response;
      serializeJson(responseDoc, response);
      ws.textAll(response);
    }
    else if (action == "saveSettings") {
      String apSSID = doc["apSSID"];
      String apPassword = doc["apPassword"];
      int apChannel = doc["apChannel"];
      bool apHidden = doc["apHidden"];
      String webUsername = doc["webUsername"];
      String webPassword = doc["webPassword"];
      bool darkMode = doc["darkMode"];
      String logLevel = doc["logLevel"];
      int refreshRate = doc["refreshRate"];
      bool powerSaveMode = doc["powerSaveMode"];
      int sleepTimeout = doc["sleepTimeout"];
      
      settings.saveAPSettings(apSSID, apPassword, apChannel, apHidden);
      settings.saveWebSettings(webUsername, webPassword, darkMode, logLevel, refreshRate);
      settings.savePowerSettings(powerSaveMode, sleepTimeout);
      
      // Notify clients
      DynamicJsonDocument responseDoc(256);
      responseDoc["type"] = "settingsSaved";
      responseDoc["success"] = true;
      
      String response;
      serializeJson(responseDoc, response);
      ws.textAll(response);
    }
    else if (action == "resetSettings") {
      settings.resetToDefault();
      
      // Notify clients
      DynamicJsonDocument responseDoc(256);
      responseDoc["type"] = "settingsReset";
      responseDoc["success"] = true;
      
      String response;
      serializeJson(responseDoc, response);
      ws.textAll(response);
    }
    else if (action == "restart") {
      // Notify clients
      DynamicJsonDocument responseDoc(256);
      responseDoc["type"] = "restarting";
      
      String response;
      serializeJson(responseDoc, response);
      ws.textAll(response);
      
      delay(1000);
      ESP.restart();
    }
    else if (action == "getSystemInfo") {
      String info = getSystemInfo();
      ws.textAll(info);
    }
  }
}

void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      connectedClients++;
      sendStatusUpdate();
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      connectedClients--;
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}