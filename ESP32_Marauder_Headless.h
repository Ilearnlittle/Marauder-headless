/**
 * ESP32 Marauder Headless Firmware with Web Control
 * Designed for ESP32 WROOM-32 with 4MB Flash
 * 
 * This firmware implements ESP32 Marauder features in a headless configuration,
 * controllable entirely via a web browser interface accessible over Wi-Fi.
 * 
 * Flash Partition Layout:
 * - Firmware: ~1.4MB
 * - SPIFFS (for web files): ~1.0MB
 * - Free/OTA: ~1.6MB
 */

#ifndef ESP32_MARAUDER_HEADLESS_H
#define ESP32_MARAUDER_HEADLESS_H

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <DNSServer.h>
#include <Update.h>
#include <esp_wifi.h>
#include <esp_wifi_types.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <esp_event.h>
#include <esp_bt.h>
#include <esp_bt_main.h>
#include <esp_gap_ble_api.h>

// Forward declarations for classes
class WiFiScan {
public:
  void begin();
  void startScan(int channel, int scanTime);
  int getNetworkCount();
  String getSSID(int index);
  String getBSSID(int index);
  int getChannel(int index);
  int getRSSI(int index);
  String getEncryption(int index);
};

class PacketMonitor {
public:
  void begin();
  void start(int channel, String filter, bool savePcap);
  void stop();
  void handleMonitor();
  int getPacketsPerSecond();
  int getTotalPackets();
};

class SSIDList {
public:
  void begin();
};

class EvilTwin {
public:
  void begin();
  void start(String ssid, int channel, bool captivePortal, String portalType);
  void stop();
  bool isActive();
private:
  bool active = false;
};

class DeauthController {
public:
  void start(String target, String mode, int packets, bool continuous);
  void stop();
  void handleDeauth();
  int getPacketsPerSecond();
  int getTotalPackets();
};

class BeaconSpam {
public:
  void start(String mode, int count, int interval, String ssids);
  void stop();
  void handleBeacon();
  int getBeaconsPerSecond();
  int getTotalBeacons();
};

class ProbeCapture {
public:
  void start(bool hopping, int channel, bool savePcap);
  void stop();
  void handleCapture();
  int getProbesPerSecond();
  int getTotalProbes();
};

class BLEScanner {
public:
  void begin();
  void startScan(int scanTime);
  int getDeviceCount();
  String getDeviceName(int index);
  String getDeviceAddress(int index);
  int getDeviceRSSI(int index);
  String getDeviceManufacturer(int index);
};

class HandshakeCapture {
public:
  void start(String ssid, int channel, bool autoDeauth);
  void stop();
  void handleCapture();
};

class FileSystem {
public:
  void begin();
};

class Settings {
public:
  void begin();
  void resetToDefault();
  void saveAPSettings(String ssid, String password, int channel, bool hidden);
  void saveWebSettings(String username, String password, bool darkMode, String logLevel, int refreshRate);
  void savePowerSettings(bool powerSaveMode, int sleepTimeout);
  String getAPSSID();
  String getAPPassword();
  int getAPChannel();
};

// Function prototypes
void setupAP();
void setupWebServer();
void notFound(AsyncWebServerRequest *request);
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
void sendStatusUpdate();
String getMACAddress();
String getSystemInfo();
void parseCommand(String command);

#endif // ESP32_MARAUDER_HEADLESS_H