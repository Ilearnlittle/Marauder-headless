#include "ESP32_Marauder_Headless.h"

extern AsyncWebSocket ws;
extern unsigned long uptime;
extern String currentOperation;
extern bool isRunning;
extern int connectedClients;
extern PacketMonitor packetMonitor;
extern ProbeCapture probeCapture;
extern DeauthController deauthController;
extern BeaconSpam beaconSpam;

void sendStatusUpdate() {
  DynamicJsonDocument doc(1024);
  doc["type"] = "status";
  doc["uptime"] = uptime;
  doc["freeMemory"] = ESP.getFreeHeap();
  doc["flashSize"] = ESP.getFlashChipSize();
  doc["operation"] = currentOperation;
  doc["running"] = isRunning;
  doc["connectedClients"] = connectedClients;
  doc["macAddress"] = getMACAddress();
  doc["apSSID"] = WiFi.softAPSSID();
  doc["apIP"] = WiFi.softAPIP().toString();
  
  // Add operation-specific status
  if (currentOperation == "packet") {
    doc["packetsPerSecond"] = packetMonitor.getPacketsPerSecond();
    doc["totalPackets"] = packetMonitor.getTotalPackets();
  } 
  else if (currentOperation == "probe") {
    doc["probesPerSecond"] = probeCapture.getProbesPerSecond();
    doc["totalProbes"] = probeCapture.getTotalProbes();
  } 
  else if (currentOperation == "deauth") {
    doc["packetsPerSecond"] = deauthController.getPacketsPerSecond();
    doc["totalPackets"] = deauthController.getTotalPackets();
  } 
  else if (currentOperation == "beacon") {
    doc["beaconsPerSecond"] = beaconSpam.getBeaconsPerSecond();
    doc["totalBeacons"] = beaconSpam.getTotalBeacons();
  }
  
  // Check battery level if connected
  float batteryVoltage = 0.0;
  if (batteryVoltage > 0) {
    doc["batteryVoltage"] = batteryVoltage;
    doc["batteryLevel"] = map(batteryVoltage * 100, 320, 420, 0, 100);
  }
  
  String status;
  serializeJson(doc, status);
  ws.textAll(status);
}

String getMACAddress() {
  uint8_t mac[6];
  WiFi.macAddress(mac);
  char macStr[18] = { 0 };
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(macStr);
}

String getSystemInfo() {
  DynamicJsonDocument doc(2048);
  doc["type"] = "systemInfo";
  doc["chipModel"] = "ESP32 WROOM-32";
  doc["flashSize"] = ESP.getFlashChipSize() / 1024 / 1024;  // Convert to MB
  doc["freeHeap"] = ESP.getFreeHeap() / 1024;  // Convert to KB
  doc["macAddress"] = getMACAddress();
  doc["firmwareVersion"] = "Marauder v1.0";
  doc["sdkVersion"] = ESP.getSdkVersion();
  
  // Storage information
  size_t totalBytes = SPIFFS.totalBytes();
  size_t usedBytes = SPIFFS.usedBytes();
  doc["spiffsTotal"] = totalBytes / 1024;  // Convert to KB
  doc["spiffsUsed"] = usedBytes / 1024;    // Convert to KB
  doc["spiffsFree"] = (totalBytes - usedBytes) / 1024;  // Convert to KB
  
  // Network information
  doc["apSSID"] = WiFi.softAPSSID();
  doc["apIP"] = WiFi.softAPIP().toString();
  doc["apClients"] = WiFi.softAPgetStationNum();
  
  String info;
  serializeJson(doc, info);
  return info;
}