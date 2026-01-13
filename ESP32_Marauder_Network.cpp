#include "ESP32_Marauder_Headless.h"
#include "web_content.h"

extern AsyncWebServer server;
extern AsyncWebSocket ws;
extern DNSServer dnsServer;
extern WiFiScan wifiScan;
extern EvilTwin evilTwin;
extern Settings settings;
extern int connectedClients;
extern String currentOperation;
extern bool isRunning;

void setupAP() {
  // Load AP settings from preferences if available, otherwise use defaults
  String ssid = settings.getAPSSID();
  String password = settings.getAPPassword();
  int channel = settings.getAPChannel();
  
  if (ssid.length() == 0) ssid = DEFAULT_AP_SSID;
  if (password.length() == 0 || password.length() < 8) password = DEFAULT_AP_PASSWORD;
  if (channel < 1 || channel > 13) channel = DEFAULT_AP_CHANNEL;

  // Start Access Point
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid.c_str(), password.c_str(), channel);
  
  Serial.print("AP Started with SSID: ");
  Serial.println(ssid);
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
}

void setupWebServer() {
  // Initialize WebSocket
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);
  
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    // Sends your index_html string from web_content.h
    request->send(200, "text/html", index_html);
  });
  
  // Since style and script are now inside index_html, we send 
  // empty responses or redirect to / to prevent "404 Not Found" errors.
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/css", ""); 
  });
  
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "application/javascript", "");
  });
}
  
  // API endpoints
  server.on("/api/scan", HTTP_GET, [](AsyncWebServerRequest *request){
    String scanType = request->hasParam("type") ? request->getParam("type")->value() : "wifi";
    int scanTime = request->hasParam("time") ? request->getParam("time")->value().toInt() : 10;
    int channel = request->hasParam("channel") ? request->getParam("channel")->value().toInt() : 0;
    
    DynamicJsonDocument doc(4096);
    
    if (scanType == "wifi") {
      wifiScan.startScan(channel, scanTime);
      JsonArray networks = doc.createNestedArray("networks");
      
      for (int i = 0; i < wifiScan.getNetworkCount(); i++) {
        JsonObject network = networks.createNestedObject();
        network["ssid"] = wifiScan.getSSID(i);
        network["bssid"] = wifiScan.getBSSID(i);
        network["channel"] = wifiScan.getChannel(i);
        network["rssi"] = wifiScan.getRSSI(i);
        network["encryption"] = wifiScan.getEncryption(i);
      }
    }
    else if (scanType == "ble") {
      bleScanner.startScan(scanTime);
      JsonArray devices = doc.createNestedArray("devices");
      
      for (int i = 0; i < bleScanner.getDeviceCount(); i++) {
        JsonObject device = devices.createNestedObject();
        device["name"] = bleScanner.getDeviceName(i);
        device["address"] = bleScanner.getDeviceAddress(i);
        device["rssi"] = bleScanner.getDeviceRSSI(i);
        device["manufacturer"] = bleScanner.getDeviceManufacturer(i);
      }
    }
    
    String response;
    serializeJson(doc, response);
    request->send(200, "application/json", response);
  });
  
  // File operations
  server.on("/api/files", HTTP_GET, [](AsyncWebServerRequest *request){
    DynamicJsonDocument doc(8192);
    JsonArray files = doc.createNestedArray("files");
    
    File root = SPIFFS.open("/captures");
    if (!root) {
      SPIFFS.mkdir("/captures");
      root = SPIFFS.open("/captures");
    }
    
    File file = root.openNextFile();
    while (file) {
      if (!file.isDirectory()) {
        JsonObject fileObj = files.createNestedObject();
        fileObj["name"] = String(file.name()).substring(9); // Remove /captures/ prefix
        fileObj["size"] = file.size();
        fileObj["timestamp"] = file.getLastWrite();
        
        // Determine file type
        String fileName = file.name();
        if (fileName.endsWith(".pcap")) {
          fileObj["type"] = "pcap";
        } else if (fileName.endsWith(".txt")) {
          fileObj["type"] = "txt";
        } else if (fileName.endsWith(".json")) {
          fileObj["type"] = "json";
        } else {
          fileObj["type"] = "unknown";
        }
      }
      file = root.openNextFile();
    }
    
    String response;
    serializeJson(doc, response);
    request->send(200, "application/json", response);
  });
  
  // Download file
  server.on("/api/download", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("file")) {
      String fileName = request->getParam("file")->value();
      String filePath = "/captures/" + fileName;
      
      if (SPIFFS.exists(filePath)) {
        request->send(SPIFFS, filePath, "application/octet-stream", true);
      } else {
        request->send(404, "text/plain", "File not found");
      }
    } else {
      request->send(400, "text/plain", "Missing file parameter");
    }
  });
  
  // Delete file
  server.on("/api/delete", HTTP_GET, [](AsyncWebServerRequest *request){
    if (request->hasParam("file")) {
      String fileName = request->getParam("file")->value();
      String filePath = "/captures/" + fileName;
      
      if (SPIFFS.exists(filePath)) {
        SPIFFS.remove(filePath);
        request->send(200, "text/plain", "File deleted");
      } else {
        request->send(404, "text/plain", "File not found");
      }
    } else {
      request->send(400, "text/plain", "Missing file parameter");
    }
  });
  
  // OTA firmware update
  server.on("/update", HTTP_POST, [](AsyncWebServerRequest *request) {
    bool shouldReboot = !Update.hasError();
    AsyncWebServerResponse *response = request->beginResponse(200, "text/plain", shouldReboot ? "OK" : "FAIL");
    response->addHeader("Connection", "close");
    request->send(response);
    if (shouldReboot) {
      delay(1000);
      ESP.restart();
    }
  }, [](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
    if (!index) {
      Serial.println("Update started");
      Serial.print("Firmware file: ");
      Serial.println(filename);
      if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
        Update.printError(Serial);
      }
    }
    
    if (Update.write(data, len) != len) {
      Update.printError(Serial);
    }
    
    if (final) {
      if (Update.end(true)) {
        Serial.println("Update success");
      } else {
        Update.printError(Serial);
      }
    }
  });
  
  // Handle 404
  server.onNotFound(notFound);
  
  // Start server
  server.begin();
}

void notFound(AsyncWebServerRequest *request) {
  // If we're running a captive portal for Evil Twin, redirect to our portal
  if (evilTwin.isActive() && request->host() != WiFi.softAPIP().toString()) {
    // Redirect to captive portal
    request->redirect("http://" + WiFi.softAPIP().toString());
  } else {
    // Normal 404
    request->send(404, "text/plain", "Not found");
  }
}
