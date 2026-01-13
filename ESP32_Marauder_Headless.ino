#include "ESP32_Marauder_Headless.h"

// Default AP credentials
const char* DEFAULT_AP_SSID = "Marauder_AP";
const char* DEFAULT_AP_PASSWORD = "marauder123";
const int DEFAULT_AP_CHANNEL = 1;

// Web server
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// DNS server for captive portal
DNSServer dnsServer;
const byte DNS_PORT = 53;

// Settings
Settings settings;

// Component instances
WiFiScan wifiScan;
PacketMonitor packetMonitor;
SSIDList ssidList;
EvilTwin evilTwin;
DeauthController deauthController;
BeaconSpam beaconSpam;
ProbeCapture probeCapture;
BLEScanner bleScanner;
HandshakeCapture handshakeCapture;
FileSystem fileSystem;

// Status variables
bool isRunning = false;
String currentOperation = "none";
unsigned long startTime = 0;
unsigned long uptime = 0;
int connectedClients = 0;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);
  delay(1000);
  Serial.println("\nESP32 Marauder Headless Firmware Starting...");

  // Initialize NVS
  if (nvs_flash_init() != ESP_OK) {
    Serial.println("Error initializing NVS, attempting to erase and reinitialize");
    ESP_ERROR_CHECK(nvs_flash_erase());
    ESP_ERROR_CHECK(nvs_flash_init());
  }

  // Initialize SPIFFS
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Initialize system components
  settings.begin();
  fileSystem.begin();
  
  // Setup WiFi Access Point
  setupAP();
  
  // Initialize web server and WebSocket
  setupWebServer();

  // Initialize WiFi scanning capabilities
  wifiScan.begin();
  
  // Initialize packet monitoring
  packetMonitor.begin();
  
  // Initialize BLE scanner
  bleScanner.begin();

  // Record start time for uptime calculation
  startTime = millis();
  
  Serial.println("ESP32 Marauder Headless Firmware Started");
  Serial.println("Access Point SSID: " + String(DEFAULT_AP_SSID));
  Serial.println("Access Point Password: " + String(DEFAULT_AP_PASSWORD));
  Serial.println("Access Point IP: 192.168.4.1");
}

void loop() {
  // Handle DNS requests for captive portal if active
  if (evilTwin.isActive()) {
    dnsServer.processNextRequest();
  }
  
  // Update uptime
  uptime = millis() - startTime;
  
  // Handle active operations
  if (isRunning) {
    if (currentOperation == "deauth") {
      deauthController.handleDeauth();
    } 
    else if (currentOperation == "beacon") {
      beaconSpam.handleBeacon();
    } 
    else if (currentOperation == "probe") {
      probeCapture.handleCapture();
    } 
    else if (currentOperation == "packet") {
      packetMonitor.handleMonitor();
    } 
    else if (currentOperation == "handshake") {
      handshakeCapture.handleCapture();
    }
  }
  
  // Send status updates to clients every second
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate > 1000) {
    sendStatusUpdate();
    lastUpdate = millis();
  }
  
  // Cleanup WebSocket clients
  ws.cleanupClients();
}