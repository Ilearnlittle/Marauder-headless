#ifndef WEB_CONTENT_H
#define WEB_CONTENT_H

// --- HTML SECTION ---
const char index_html[] PROGMEM = R"rawcanvas(
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Marauder Headless</title>
    <style>
)rawcanvas" 
:root {
    --primary-color: #2196F3;
    --secondary-color: #03A9F4;
    --danger-color: #F44336;
    --warning-color: #FFC107;
    --success-color: #4CAF50;
    --text-color: #333;
    --text-secondary: #666;
    --background-color: #f5f5f5;
    --card-bg: #fff;
    --border-color: #ddd;
    --header-bg: #1976D2;
    --header-text: #fff;
    --nav-active: #E3F2FD;
    --nav-hover: #f0f0f0;
    --shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
    --firmware-color: #ff9800;
    --spiffs-color: #03a9f4;
    --free-color: #4caf50;
}

body.dark-mode {
    --primary-color: #2196F3;
    --secondary-color: #0288D1;
    --danger-color: #F44336;
    --warning-color: #FFC107;
    --success-color: #4CAF50;
    --text-color: #f0f0f0;
    --text-secondary: #aaa;
    --background-color: #121212;
    --card-bg: #1e1e1e;
    --border-color: #333;
    --header-bg: #0d47a1;
    --header-text: #fff;
    --nav-active: #1565C0;
    --nav-hover: #333;
    --shadow: 0 2px 4px rgba(0, 0, 0, 0.3);
    --firmware-color: #ff9800;
    --spiffs-color: #03a9f4;
    --free-color: #4caf50;
}

* {
    box-sizing: border-box;
    margin: 0;
    padding: 0;
}

body {
    font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
    background-color: var(--background-color);
    color: var(--text-color);
    line-height: 1.6;
}

.container {
    max-width: 1200px;
    margin: 0 auto;
    padding: 0;
}

/* Header Styles */
header {
    background-color: var(--header-bg);
    color: var(--header-text);
    padding: 1rem;
    box-shadow: var(--shadow);
}

header h1 {
    margin: 0;
    font-size: 1.8rem;
    display: flex;
    align-items: center;
}

header h1 i {
    margin-right: 10px;
}

.status-bar {
    display: flex;
    flex-wrap: wrap;
    margin-top: 10px;
    font-size: 0.9rem;
}

.status-item {
    margin-right: 20px;
    display: flex;
    align-items: center;
}

.status-item i {
    margin-right: 5px;
}

/* Navigation Styles */
nav {
    background-color: var(--card-bg);
    box-shadow: var(--shadow);
}

nav ul {
    display: flex;
    list-style: none;
    overflow-x: auto;
    padding: 0;
}

.nav-item {
    padding: 15px 20px;
    cursor: pointer;
    white-space: nowrap;
    transition: background-color 0.3s;
    display: flex;
    align-items: center;
    border-bottom: 3px solid transparent;
}

.nav-item i {
    margin-right: 8px;
}

.nav-item:hover {
    background-color: var(--nav-hover);
}

.nav-item.active {
    background-color: var(--nav-active);
    color: var(--primary-color);
    border-bottom: 3px solid var(--primary-color);
    font-weight: bold;
}

/* Main Content */
main {
    padding: 20px 10px;
}

.content-section {
    display: none;
}

.content-section.active {
    display: block;
}

.section-header {
    margin-bottom: 20px;
    border-bottom: 1px solid var(--border-color);
    padding-bottom: 10px;
}

.section-header h2 {
    font-size: 1.5rem;
}

/* Card Styles */
.card, .attack-card, .control-card, .settings-card {
    background-color: var(--card-bg);
    border-radius: 5px;
    box-shadow: var(--shadow);
    margin-bottom: 20px;
    overflow: hidden;
}

.card-header, .attack-header, .settings-header {
    background-color: var(--primary-color);
    color: white;
    padding: 10px 15px;
}

.card-body, .attack-body, .settings-body {
    padding: 15px;
}

/* Dashboard Styles */
.dashboard-cards {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
    gap: 20px;
    margin-bottom: 20px;
}

.quick-actions {
    display: grid;
    grid-template-columns: repeat(2, 1fr);
    gap: 10px;
}

/* Log Styles */
.log-container, .attack-log-container, .sniffer-results {
    background-color: var(--card-bg);
    border-radius: 5px;
    box-shadow: var(--shadow);
    margin-bottom: 20px;
    height: 300px;
    display: flex;
    flex-direction: column;
}

.log-header, .results-header {
    padding: 10px 15px;
    background-color: var(--primary-color);
    color: white;
    display: flex;
    justify-content: space-between;
    align-items: center;
}

.log-content, .live-data-container {
    padding: 10px;
    overflow-y: auto;
    flex: 1;
    font-family: monospace;
    background-color: #1e1e1e;
    color: #f0f0f0;
}

.log-entry {
    margin-bottom: 5px;
    border-bottom: 1px solid #333;
    padding-bottom: 5px;
}

/* Button Styles */
button {
    padding: 8px 15px;
    border: none;
    border-radius: 4px;
    cursor: pointer;
    font-size: 0.9rem;
    transition: background-color 0.3s, transform 0.1s;
    display: inline-flex;
    align-items: center;
    justify-content: center;
}

button:active {
    transform: translateY(1px);
}

button i {
    margin-right: 5px;
}

button.primary {
    background-color: var(--primary-color);
    color: white;
}

button.primary:hover {
    background-color: var(--secondary-color);
}

button.danger {
    background-color: var(--danger-color);
    color: white;
}

button.danger:hover {
    background-color: #d32f2f;
}

button.warning {
    background-color: var(--warning-color);
    color: #333;
}

button.warning:hover {
    background-color: #ffb300;
}

button:disabled {
    background-color: #ccc;
    cursor: not-allowed;
}

/* Input Styles */
.input-group {
    margin-bottom: 15px;
}

.input-group label {
    display: block;
    margin-bottom: 5px;
    font-weight: 500;
}

input[type="text"], 
input[type="password"], 
input[type="number"], 
select, 
textarea {
    width: 100%;
    padding: 8px 12px;
    border: 1px solid var(--border-color);
    border-radius: 4px;
    font-size: 0.9rem;
    background-color: var(--card-bg);
    color: var(--text-color);
}

input[type="range"] {
    width: 90%;
    vertical-align: middle;
}

.input-group.checkbox {
    display: flex;
    align-items: center;
}

.input-group.checkbox label {
    margin-bottom: 0;
    margin-left: 5px;
}

input[type="checkbox"], input[type="radio"] {
    margin-right: 5px;
}

/* WiFi Attack Styles */
.attack-options {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
    gap: 20px;
}

/* Scanner and Sniffer Styles */
.scanner-controls, .sniffer-controls {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
    gap: 20px;
    margin-bottom: 20px;
}

/* Results and Tables */
.results-container, .captures-container, .settings-container {
    background-color: var(--card-bg);
    border-radius: 5px;
    box-shadow: var(--shadow);
    overflow: hidden;
}

.results-controls {
    display: flex;
}

.results-controls button {
    margin-left: 10px;
}

.results-tabs {
    display: flex;
    background-color: var(--card-bg);
    border-bottom: 1px solid var(--border-color);
}

.tab {
    padding: 10px 20px;
    cursor: pointer;
    border-bottom: 2px solid transparent;
}

.tab.active {
    border-bottom: 2px solid var(--primary-color);
    color: var(--primary-color);
    font-weight: bold;
}

.tab-content {
    display: none;
    padding: 10px;
}

.tab-content.active {
    display: block;
}

.results-table {
    width: 100%;
    border-collapse: collapse;
}

.results-table th, 
.results-table td {
    padding: 10px;
    text-align: left;
    border-bottom: 1px solid var(--border-color);
}

.results-table th {
    background-color: rgba(0, 0, 0, 0.05);
    font-weight: 600;
}

.action-btn {
    padding: 5px;
    margin-right: 5px;
    background: none;
    border: 1px solid var(--border-color);
}

.action-btn:hover {
    background-color: var(--nav-hover);
}

/* Captures Section */
.captures-container {
    display: grid;
    grid-template-columns: 1fr;
    grid-template-rows: auto 1fr;
}

.capture-filters {
    padding: 15px;
    display: flex;
    gap: 20px;
    border-bottom: 1px solid var(--border-color);
}

.captures-list {
    padding: 15px;
    overflow: auto;
    max-height: 400px;
}

.captures-preview {
    padding: 15px;
    border-top: 1px solid var(--border-color);
}

.preview-header {
    margin-bottom: 10px;
}

.preview-content {
    background-color: #1e1e1e;
    color: #f0f0f0;
    padding: 10px;
    border-radius: 4px;
    height: 200px;
    overflow: auto;
    font-family: monospace;
}

.preview-placeholder {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    height: 100%;
    color: #666;
}

.preview-placeholder i {
    font-size: 2rem;
    margin-bottom: 10px;
}

/* Settings Section */
.settings-container {
    padding: 0;
}

.settings-group {
    margin-bottom: 20px;
}

.settings-group h4 {
    margin-bottom: 10px;
    border-bottom: 1px solid var(--border-color);
    padding-bottom: 5px;
}

.button-group {
    display: flex;
    gap: 10px;
}

.mt-20 {
    margin-top: 20px;
}

.hint {
    font-size: 0.8rem;
    color: var(--text-secondary);
    margin-left: 5px;
}

/* Memory Bar Styles */
.memory-bar-container {
    margin-bottom: 15px;
}

.memory-label {
    margin-bottom: 5px;
    font-weight: 500;
}

.memory-bar {
    height: 25px;
    display: flex;
    border-radius: 4px;
    overflow: hidden;
}

.memory-segment {
    height: 100%;
    display: flex;
    align-items: center;
    justify-content: center;
    color: white;
    font-size: 0.8rem;
    text-shadow: 0 0 2px rgba(0, 0, 0, 0.5);
}

.memory-segment.firmware {
    background-color: var(--firmware-color);
}

.memory-segment.spiffs {
    background-color: var(--spiffs-color);
}

.memory-segment.free {
    background-color: var(--free-color);
}

/* Modal Styles */
.modal {
    display: none;
    position: fixed;
    top: 0;
    left: 0;
    width: 100%;
    height: 100%;
    background-color: rgba(0, 0, 0, 0.5);
    z-index: 1000;
    align-items: center;
    justify-content: center;
}

.modal.active {
    display: flex;
}

.modal-content {
    background-color: var(--card-bg);
    border-radius: 5px;
    width: 90%;
    max-width: 500px;
    box-shadow: 0 4px 8px rgba(0, 0, 0, 0.2);
}

.modal-header {
    padding: 15px;
    display: flex;
    justify-content: space-between;
    align-items: center;
    border-bottom: 1px solid var(--border-color);
}

.modal-body {
    padding: 15px;
    max-height: 70vh;
    overflow-y: auto;
}

.modal-footer {
    padding: 15px;
    text-align: right;
    border-top: 1px solid var(--border-color);
}

.close-modal {
    background: none;
    border: none;
    font-size: 1.5rem;
    cursor: pointer;
    padding: 0;
    color: var(--text-color);
}

.warning-message {
    padding: 10px;
    background-color: rgba(255, 193, 7, 0.1);
    border-left: 3px solid var(--warning-color);
    margin: 15px 0;
    display: flex;
    align-items: center;
}

.warning-message i {
    color: var(--warning-color);
    margin-right: 10px;
    font-size: 1.2rem;
}

.file-upload {
    position: relative;
}

.file-upload input[type="file"] {
    opacity: 0;
    position: absolute;
    width: 100%;
    height: 40px;
    cursor: pointer;
}

.file-upload .file-name {
    padding: 8px 12px;
    border: 1px solid var(--border-color);
    border-radius: 4px;
    background-color: var(--card-bg);
    color: var(--text-color);
    width: 100%;
    margin-top: 5px;
}

.radio-group {
    margin-bottom: 10px;
}

.hidden {
    display: none;
}

.radio-group {
    display: flex;
    align-items: center;
}

/* Mobile Responsiveness */
@media (max-width: 768px) {
    .dashboard-cards, .attack-options, .scanner-controls, .sniffer-controls {
        grid-template-columns: 1fr;
    }

    .button-group {
        flex-direction: column;
    }

    .status-bar {
        flex-direction: column;
    }

    .status-item {
        margin-right: 0;
        margin-bottom: 5px;
    }

    .capture-filters {
        flex-direction: column;
    }
}

/* Animation for loading/processing */
@keyframes spin {
    0% { transform: rotate(0deg); }
    100% { transform: rotate(360deg); }
}

.loading {
    position: relative;
}

.loading::after {
    content: '';
    position: absolute;
    top: 50%;
    left: 50%;
    margin: -10px 0 0 -10px;
    width: 20px;
    height: 20px;
    border: 3px solid rgba(255,255,255,0.3);
    border-top: 3px solid #fff;
    border-radius: 50%;
    animation: spin 1s linear infinite;
}

/* Live data styles */
#live-data {
    font-family: monospace;
    font-size: 0.9rem;
    line-height: 1.4;
}

.packet-item {
    padding: 5px;
    margin-bottom: 5px;
    border-bottom: 1px solid #333;
}

.packet-item.mgmt {
    border-left: 3px solid var(--primary-color);
}

.packet-item.data {
    border-left: 3px solid var(--success-color);
}

.packet-item.ctrl {
    border-left: 3px solid var(--warning-color);
}

/* Tooltip styles */
.tooltip {
    position: relative;
    display: inline-block;
}

.tooltip .tooltiptext {
    visibility: hidden;
    width: 200px;
    background-color: #333;
    color: #fff;
    text-align: center;
    border-radius: 6px;
    padding: 5px;
    position: absolute;
    z-index: 1;
    bottom: 125%;
    left: 50%;
    transform: translateX(-50%);
    opacity: 0;
    transition: opacity 0.3s;
}

.tooltip:hover .tooltiptext {
    visibility: visible;
    opacity: 1;
}

/* Progress bar */
.progress-container {
    width: 100%;
    background-color: var(--border-color);
    border-radius: 4px;
    margin: 10px 0;
}

.progress-bar {
    height: 20px;
    background-color: var(--primary-color);
    border-radius: 4px;
    text-align: center;
    color: white;
    font-size: 0.8rem;
    line-height: 20px;
    transition: width 0.3s ease;
}
// --- PASTE ALL YOUR style.css CONTENT HERE ---

R"rawcanvas(
    </style>
</head>
<body>
)rawcanvas" 
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Marauder Headless Controller</title>
    <link rel="stylesheet" href="./style.css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css">
</head>

<body>
    <div class="container">
        <header>
            <h1><i class="fas fa-wifi"></i> ESP32 Marauder</h1>
            <div class="status-bar">
                <div class="status-item" id="wifi-mode">
                    <i class="fas fa-broadcast-tower"></i> <span>AP Mode: Marauder_AP</span>
                </div>
                <div class="status-item" id="battery">
                    <i class="fas fa-battery-three-quarters"></i> <span>Battery: 85%</span>
                </div>
                <div class="status-item" id="uptime">
                    <i class="fas fa-clock"></i> <span>Uptime: 00:00:00</span>
                </div>
                <div class="status-item" id="clients">
                    <i class="fas fa-users"></i> <span>Clients: 1</span>
                </div>
            </div>
        </header>

        <nav id="main-nav">
            <ul>
                <li class="nav-item active" data-target="dashboard"><i class="fas fa-tachometer-alt"></i> Dashboard</li>
                <li class="nav-item" data-target="wifi-attacks"><i class="fas fa-bomb"></i> WiFi Attacks</li>
                <li class="nav-item" data-target="scanners"><i class="fas fa-search"></i> Scanners</li>
                <li class="nav-item" data-target="sniffers"><i class="fas fa-eye"></i> Sniffers</li>
                <li class="nav-item" data-target="captures"><i class="fas fa-file-download"></i> Captures</li>
                <li class="nav-item" data-target="settings"><i class="fas fa-cogs"></i> Settings</li>
            </ul>
        </nav>

        <main>
            <!-- Dashboard Section -->
            <section id="dashboard" class="content-section active">
                <div class="section-header">
                    <h2>Dashboard</h2>
                </div>
                <div class="dashboard-cards">
                    <div class="card">
                        <div class="card-header">
                            <h3>Device Info</h3>
                        </div>
                        <div class="card-body">
                            <p><strong>Model:</strong> ESP32 WROOM-32</p>
                            <p><strong>Flash Size:</strong> 4MB</p>
                            <p><strong>Firmware Version:</strong> Marauder v1.0</p>
                            <p><strong>MAC Address:</strong> <span id="mac-address">12:34:56:78:9A:BC</span></p>
                            <p><strong>Free Memory:</strong> <span id="free-memory">115,432 bytes</span></p>
                        </div>
                    </div>
                    <div class="card">
                        <div class="card-header">
                            <h3>Network Status</h3>
                        </div>
                        <div class="card-body">
                            <p><strong>AP SSID:</strong> Marauder_AP</p>
                            <p><strong>IP Address:</strong> 192.168.4.1</p>
                            <p><strong>Connected Clients:</strong> <span id="client-count">1</span></p>
                            <p><strong>Channel:</strong> 1</p>
                        </div>
                    </div>
                    <div class="card">
                        <div class="card-header">
                            <h3>Quick Actions</h3>
                        </div>
                        <div class="card-body quick-actions">
                            <button id="scan-networks"><i class="fas fa-search"></i> Scan Networks</button>
                            <button id="toggle-bluetooth"><i class="fab fa-bluetooth"></i> Toggle BLE</button>
                            <button id="restart-device"><i class="fas fa-redo"></i> Restart Device</button>
                            <button id="update-firmware"><i class="fas fa-download"></i> Update Firmware</button>
                        </div>
                    </div>
                </div>
                <div class="log-container">
                    <div class="log-header">
                        <h3>System Log</h3>
                        <button id="clear-log">Clear</button>
                    </div>
                    <div class="log-content" id="system-log">
                        <div class="log-entry">[INFO] ESP32 Marauder started successfully</div>
                        <div class="log-entry">[INFO] Flash Size: 4MB (4,194,304 bytes)</div>
                        <div class="log-entry">[INFO] Available space for captures: ~2.5MB</div>
                        <div class="log-entry">[INFO] AP mode activated: SSID: Marauder_AP</div>
                        <div class="log-entry">[INFO] Web server started on port 80</div>
                        <div class="log-entry">[INFO] Client connected: 192.168.4.2</div>
                    </div>
                </div>
            </section>

            <!-- Other sections remain the same as in the previous code -->
            <!-- WiFi Attacks Section -->
            <section id="wifi-attacks" class="content-section">
                <!-- Content from previous code -->
            </section>

            <!-- Scanners Section -->
            <section id="scanners" class="content-section">
                <!-- Content from previous code -->
            </section>

            <!-- Sniffers Section -->
            <section id="sniffers" class="content-section">
                <!-- Content from previous code -->
            </section>

            <!-- Captures Section -->
            <section id="captures" class="content-section">
                <!-- Content from previous code -->
            </section>

            <!-- Settings Section -->
            <section id="settings" class="content-section">
                <div class="section-header">
                    <h2>Settings</h2>
                </div>
                <div class="settings-container">
                    <div class="settings-card">
                        <div class="settings-header">
                            <h3>Network Settings</h3>
                        </div>
                        <div class="settings-body">
                            <div class="settings-group">
                                <h4>Access Point Mode</h4>
                                <div class="input-group">
                                    <label for="ap-ssid">SSID:</label>
                                    <input type="text" id="ap-ssid" value="Marauder_AP">
                                </div>
                                <div class="input-group">
                                    <label for="ap-password">Password:</label>
                                    <input type="password" id="ap-password" value="marauder123">
                                </div>
                                <div class="input-group">
                                    <label for="ap-channel">Channel:</label>
                                    <input type="number" id="ap-channel" min="1" max="14" value="1">
                                </div>
                                <div class="input-group checkbox">
                                    <input type="checkbox" id="ap-hidden">
                                    <label for="ap-hidden">Hidden SSID</label>
                                </div>
                            </div>
                            <div class="settings-group">
                                <h4>Station Mode</h4>
                                <div class="input-group">
                                    <label for="station-ssid">Connect to SSID:</label>
                                    <input type="text" id="station-ssid" placeholder="Enter WiFi SSID">
                                </div>
                                <div class="input-group">
                                    <label for="station-password">Password:</label>
                                    <input type="password" id="station-password" placeholder="Enter WiFi password">
                                </div>
                                <button id="connect-wifi" class="primary"><i class="fas fa-plug"></i> Connect</button>
                            </div>
                        </div>
                    </div>

                    <div class="settings-card">
                        <div class="settings-header">
                            <h3>Web Interface Settings</h3>
                        </div>
                        <div class="settings-body">
                            <div class="input-group">
                                <label for="web-username">Username:</label>
                                <input type="text" id="web-username" value="admin">
                            </div>
                            <div class="input-group">
                                <label for="web-password">Password:</label>
                                <input type="password" id="web-password" value="marauder123">
                            </div>
                            <div class="input-group checkbox">
                                <input type="checkbox" id="dark-mode">
                                <label for="dark-mode">Dark Mode</label>
                            </div>
                            <div class="input-group">
                                <label for="log-level">Log Level:</label>
                                <select id="log-level">
                                    <option value="debug">Debug</option>
                                    <option value="info" selected>Info</option>
                                    <option value="warning">Warning</option>
                                    <option value="error">Error</option>
                                </select>
                            </div>
                            <div class="input-group">
                                <label for="refresh-rate">UI Refresh Rate (ms):</label>
                                <input type="number" id="refresh-rate" min="500" max="5000" step="100" value="1000">
                            </div>
                        </div>
                    </div>

                    <div class="settings-card">
                        <div class="settings-header">
                            <h3>System Settings</h3>
                        </div>
                        <div class="settings-body">
                            <div class="input-group">
                                <label for="device-name">Device Name:</label>
                                <input type="text" id="device-name" value="ESP32-Marauder">
                            </div>
                            <div class="settings-group">
                                <h4>Memory Management</h4>
                                <div class="memory-bar-container">
                                    <div class="memory-label">Flash Usage (4MB Total):</div>
                                    <div class="memory-bar">
                                        <div class="memory-segment firmware" style="width: 35%;">Firmware (1.4MB)</div>
                                        <div class="memory-segment spiffs" style="width: 25%;">SPIFFS (1.0MB)</div>
                                        <div class="memory-segment free" style="width: 40%;">Free (1.6MB)</div>
                                    </div>
                                </div>
                                <div class="input-group">
                                    <label for="max-capture-size">Max Capture Size (KB):</label>
                                    <input type="number" id="max-capture-size" min="100" max="1500" step="100" value="500">
                                </div>
                                <div class="input-group checkbox">
                                    <input type="checkbox" id="auto-delete-old">
                                    <label for="auto-delete-old">Auto-delete Oldest Files When Full</label>
                                </div>
                            </div>
                            <div class="settings-group">
                                <h4>Power Management</h4>
                                <div class="input-group checkbox">
                                    <input type="checkbox" id="power-save-mode">
                                    <label for="power-save-mode">Power Save Mode</label>
                                </div>
                                <div class="input-group">
                                    <label for="sleep-timeout">Sleep Timeout (minutes):</label>
                                    <input type="number" id="sleep-timeout" min="0" max="60" value="0">
                                    <span class="hint">0 = Disabled</span>
                                </div>
                            </div>
                            <div class="button-group">
                                <button id="save-settings" class="primary"><i class="fas fa-save"></i> Save Settings</button>
                                <button id="reset-settings"><i class="fas fa-undo"></i> Reset to Default</button>
                            </div>
                            <div class="button-group mt-20">
                                <button id="firmware-update" class="primary"><i class="fas fa-download"></i> Firmware Update</button>
                                <button id="factory-reset" class="danger"><i class="fas fa-exclamation-triangle"></i> Factory Reset</button>
                                <button id="restart-esp" class="warning"><i class="fas fa-power-off"></i> Restart Device</button>
                            </div>
                        </div>
                    </div>
                </div>
            </section>
        </main>
    </div>

    <!-- Modals -->
    <div class="modal" id="firmware-update-modal">
        <div class="modal-content">
            <div class="modal-header">
                <h3>Firmware Update</h3>
                <button class="close-modal">&times;</button>
            </div>
            <div class="modal-body">
                <div class="update-options">
                    <div class="option-group">
                        <h4>Update Method</h4>
                        <div class="radio-group">
                            <input type="radio" id="ota-update" name="update-method" checked>
                            <label for="ota-update">OTA Update (from URL)</label>
                        </div>
                        <div class="radio-group">
                            <input type="radio" id="file-update" name="update-method">
                            <label for="file-update">Upload Firmware File</label>
                        </div>
                    </div>

                    <div id="ota-update-form">
                        <div class="input-group">
                            <label for="firmware-url">Firmware URL:</label>
                            <input type="text" id="firmware-url" placeholder="https://example.com/firmware.bin">
                        </div>
                    </div>

                    <div id="file-update-form" class="hidden">
                        <div class="input-group file-upload">
                            <label for="firmware-file">Select Firmware File:</label>
                            <input type="file" id="firmware-file" accept=".bin">
                            <div class="file-name">No file selected</div>
                        </div>
                    </div>

                    <div class="warning-message">
                        <i class="fas fa-exclamation-triangle"></i>
                        <span>Warning: Updating firmware may take several minutes. Do not power off the device during the update process.</span>
                    </div>
                </div>
            </div>
            <div class="modal-footer">
                <button class="cancel-update">Cancel</button>
                <button class="start-update primary">Start Update</button>
            </div>
        </div>
    </div>

    <div class="modal" id="confirm-modal">
        <div class="modal-content">
            <div class="modal-header">
                <h3 id="confirm-title">Confirm Action</h3>
                <button class="close-modal">&times;</button>
            </div>
            <div class="modal-body">
                <p id="confirm-message">Are you sure you want to perform this action?</p>
            </div>
            <div class="modal-footer">
                <button class="cancel-action">Cancel</button>
                <button id="confirm-action" class="danger">Confirm</button>
            </div>
        </div>
    </div>

    <script type="module" src="./script.js"></script>
</body>

</html>
// --- PASTE ALL YOUR index.html (only the <body> part) HERE ---

R"rawcanvas(
    <script>
)rawcanvas" 
document.addEventListener('DOMContentLoaded', function() {
    // Initialize the system
    initNavigation();
    initToggleElements();
    initRangeInputs();
    initModalHandlers();
    initActionHandlers();
    initTabHandlers();
    startStatusUpdates();
    
    // Add a simulated system log entry
    addLogEntry('[INFO] Web interface loaded successfully');
});

// Navigation between sections
function initNavigation() {
    const navItems = document.querySelectorAll('.nav-item');
    navItems.forEach(item => {
        item.addEventListener('click', function() {
            const target = this.getAttribute('data-target');
            
            // Update active nav item
            document.querySelectorAll('.nav-item').forEach(nav => {
                nav.classList.remove('active');
            });
            this.classList.add('active');
            
            // Show selected section, hide others
            document.querySelectorAll('.content-section').forEach(section => {
                section.classList.remove('active');
            });
            document.getElementById(target).classList.add('active');
        });
    });
}

// Initialize toggle elements like checkboxes that show/hide related inputs
function initToggleElements() {
    // For probe request channel hopping
    const probeHopping = document.getElementById('probe-hopping');
    const probeChannelContainer = document.getElementById('probe-channel-container');
    
    if (probeHopping && probeChannelContainer) {
        probeHopping.addEventListener('change', function() {
            if (this.checked) {
                probeChannelContainer.style.opacity = '0.5';
                probeChannelContainer.querySelector('input').disabled = true;
            } else {
                probeChannelContainer.style.opacity = '1';
                probeChannelContainer.querySelector('input').disabled = false;
            }
        });
    }
    
    // For beacon spam custom SSIDs
    const beaconMode = document.getElementById('beacon-mode');
    const customSsidContainer = document.getElementById('custom-ssid-container');
    
    if (beaconMode && customSsidContainer) {
        beaconMode.addEventListener('change', function() {
            customSsidContainer.style.display = this.value === 'custom' ? 'block' : 'none';
        });
    }
    
    // For evil twin captive portal
    const evilTwinCaptive = document.getElementById('evil-twin-captive');
    const portalOptions = document.getElementById('portal-options');
    
    if (evilTwinCaptive && portalOptions) {
        evilTwinCaptive.addEventListener('change', function() {
            portalOptions.style.display = this.checked ? 'block' : 'none';
        });
    }
    
    // Dark mode toggle
    const darkMode = document.getElementById('dark-mode');
    if (darkMode) {
        // Check for saved dark mode preference
        const isDarkMode = localStorage.getItem('darkMode') === 'true';
        darkMode.checked = isDarkMode;
        
        if (isDarkMode) {
            document.body.classList.add('dark-mode');
        }
        
        darkMode.addEventListener('change', function() {
            if (this.checked) {
                document.body.classList.add('dark-mode');
                localStorage.setItem('darkMode', 'true');
            } else {
                document.body.classList.remove('dark-mode');
                localStorage.setItem('darkMode', 'false');
            }
        });
    }
}

// Initialize range inputs with value display
function initRangeInputs() {
    const rangeInputs = [
        { input: 'deauth-packets', display: 'deauth-packets-value' },
        { input: 'beacon-count', display: 'beacon-count-value' }
    ];
    
    rangeInputs.forEach(item => {
        const input = document.getElementById(item.input);
        const display = document.getElementById(item.display);
        
        if (input && display) {
            // Initial value
            display.textContent = input.value;
            
            // Update on change
            input.addEventListener('input', function() {
                display.textContent = this.value;
            });
        }
    });
}

// Initialize modal dialogs
function initModalHandlers() {
    // Setup firmware update modal
    const updateBtn = document.getElementById('firmware-update');
    const updateModal = document.getElementById('firmware-update-modal');
    
    if (updateBtn && updateModal) {
        updateBtn.addEventListener('click', function() {
            updateModal.classList.add('active');
        });
        
        updateModal.querySelector('.close-modal').addEventListener('click', function() {
            updateModal.classList.remove('active');
        });
        
        updateModal.querySelector('.cancel-update').addEventListener('click', function() {
            updateModal.classList.remove('active');
        });
        
        updateModal.querySelector('.start-update').addEventListener('click', function() {
            updateModal.classList.remove('active');
            simulateFirmwareUpdate();
        });
    }
    
    // Setup confirm modal
    const confirmModal = document.getElementById('confirm-modal');
    const factoryResetBtn = document.getElementById('factory-reset');
    const restartEspBtn = document.getElementById('restart-esp');
    
    if (confirmModal) {
        confirmModal.querySelector('.close-modal').addEventListener('click', function() {
            confirmModal.classList.remove('active');
        });
        
        confirmModal.querySelector('.cancel-action').addEventListener('click', function() {
            confirmModal.classList.remove('active');
        });
    }
    
    if (factoryResetBtn) {
        factoryResetBtn.addEventListener('click', function() {
            document.getElementById('confirm-title').textContent = 'Factory Reset';
            document.getElementById('confirm-message').textContent = 'Are you sure you want to reset all settings to factory defaults? This action cannot be undone.';
            
            document.getElementById('confirm-action').onclick = function() {
                confirmModal.classList.remove('active');
                simulateFactoryReset();
            };
            
            confirmModal.classList.add('active');
        });
    }
    
    if (restartEspBtn) {
        restartEspBtn.addEventListener('click', function() {
            document.getElementById('confirm-title').textContent = 'Restart Device';
            document.getElementById('confirm-message').textContent = 'Are you sure you want to restart the ESP32 device?';
            
            document.getElementById('confirm-action').onclick = function() {
                confirmModal.classList.remove('active');
                simulateRestart();
            };
            
            confirmModal.classList.add('active');
        });
    }
}

// Initialize action handlers (buttons)
function initActionHandlers() {
    // WiFi Attacks section
    initAttackButtons('deauth', simulateDeauthAttack);
    initAttackButtons('beacon', simulateBeaconSpam);
    initAttackButtons('evil-twin', simulateEvilTwin);
    
    // Scanners section
    initAttackButtons('wifi-scan', simulateWiFiScan);
    initAttackButtons('ble-scan', simulateBLEScan);
    
    // Sniffers section
    initAttackButtons('packet-monitor', simulatePacketMonitor);
    initAttackButtons('probe-sniffer', simulateProbeSniffing);
    initAttackButtons('handshake', simulateHandshakeCapture);
    
    // Dashboard quick actions
    const scanBtn = document.getElementById('scan-networks');
    if (scanBtn) {
        scanBtn.addEventListener('click', function() {
            document.querySelector('[data-target="scanners"]').click();
            setTimeout(() => {
                document.getElementById('start-wifi-scan').click();
            }, 300);
        });
    }
    
    // Log controls
    const clearLogBtn = document.getElementById('clear-log');
    if (clearLogBtn) {
        clearLogBtn.addEventListener('click', function() {
            document.getElementById('system-log').innerHTML = '';
            addLogEntry('[INFO] Log cleared');
        });
    }
    
    const clearAttackLogBtn = document.getElementById('clear-attack-log');
    if (clearAttackLogBtn) {
        clearAttackLogBtn.addEventListener('click', function() {
            document.getElementById('attack-log').innerHTML = '';
        });
    }
    
    // Settings actions
    const saveSettingsBtn = document.getElementById('save-settings');
    if (saveSettingsBtn) {
        saveSettingsBtn.addEventListener('click', function() {
            addLogEntry('[INFO] Saving settings...');
            setTimeout(() => {
                addLogEntry('[INFO] Settings saved successfully');
            }, 500);
        });
    }
}

function initAttackButtons(prefix, simulationFunction) {
    const startBtn = document.getElementById(`start-${prefix}`);
    const stopBtn = document.getElementById(`stop-${prefix}`);
    
    if (startBtn && stopBtn) {
        startBtn.addEventListener('click', function() {
            this.disabled = true;
            stopBtn.disabled = false;
            simulationFunction(true);
        });
        
        stopBtn.addEventListener('click', function() {
            this.disabled = true;
            startBtn.disabled = false;
            simulationFunction(false);
        });
    }
}

// Simulation functions
function simulateDeauthAttack(isStarting) {
    if (isStarting) {
        const target = document.getElementById('deauth-target').value || 'broadcast';
        const mode = document.getElementById('deauth-mode').value;
        const packets = document.getElementById('deauth-packets').value;
        
        addLogToElement(document.getElementById('attack-log'), `[INFO] Starting deauthentication attack`);
        addLogToElement(document.getElementById('attack-log'), `[INFO] Target: ${target}`);
        addLogToElement(document.getElementById('attack-log'), `[INFO] Mode: ${mode}`);
        addLogToElement(document.getElementById('attack-log'), `[INFO] Packets per second: ${packets}`);
        
        window.deauthInterval = setInterval(() => {
            const mac = generateRandomMAC();
            addLogToElement(document.getElementById('attack-log'), `[DEAUTH] Sent deauth to ${mac}`);
        }, 1000);
    } else {
        addLogToElement(document.getElementById('attack-log'), `[INFO] Deauthentication attack stopped`);
        clearInterval(window.deauthInterval);
    }
}

function simulateBeaconSpam(isStarting) {
    if (isStarting) {
        const mode = document.getElementById('beacon-mode').value;
        const count = document.getElementById('beacon-count').value;
        const interval = document.getElementById('beacon-interval').value;
        
        addLogToElement(document.getElementById('attack-log'), `[INFO] Starting beacon spam attack`);
        addLogToElement(document.getElementById('attack-log'), `[INFO] Mode: ${mode}`);
        addLogToElement(document.getElementById('attack-log'), `[INFO] Count: ${count}`);
        addLogToElement(document.getElementById('attack-log'), `[INFO] Interval: ${interval}ms`);
        
        window.beaconInterval = setInterval(() => {
            const ssid = `Network_${Math.random().toString(36).substring(2, 6)}`;
            addLogToElement(document.getElementById('attack-log'), `[BEACON] Broadcasting: ${ssid}`);
        }, 800);
    } else {
        addLogToElement(document.getElementById('attack-log'), `[INFO] Beacon spam attack stopped`);
        clearInterval(window.beaconInterval);
    }
}

function simulateEvilTwin(isStarting) {
    if (isStarting) {
        const ssid = document.getElementById('evil-twin-ssid').value || 'Default-WiFi';
        const channel = document.getElementById('evil-twin-channel').value;
        
        addLogToElement(document.getElementById('attack-log'), `[INFO] Starting evil twin attack`);
        addLogToElement(document.getElementById('attack-log'), `[INFO] Target SSID: ${ssid}`);
        addLogToElement(document.getElementById('attack-log'), `[INFO] Channel: ${channel}`);
        
        setTimeout(() => {
            addLogToElement(document.getElementById('attack-log'), `[INFO] Evil twin AP created: ${ssid}`);
        }, 1000);
        
        window.evilTwinInterval = setInterval(() => {
            const mac = generateRandomMAC();
            addLogToElement(document.getElementById('attack-log'), `[EVIL] Client ${mac} connected`);
        }, 3000);
    } else {
        addLogToElement(document.getElementById('attack-log'), `[INFO] Evil twin attack stopped`);
        clearInterval(window.evilTwinInterval);
    }
}

function simulateWiFiScan(isStarting) {
    if (isStarting) {
        const resultsBody = document.getElementById('wifi-results-body');
        resultsBody.innerHTML = '<tr><td colspan="6">Scanning...</td></tr>';
        
        addLogEntry('[INFO] Starting WiFi scan');
        
        setTimeout(() => {
            resultsBody.innerHTML = '';
            
            // Create some sample networks
            const networks = [
                { ssid: 'Home-WiFi', bssid: '12:34:56:78:9A:BC', channel: 1, rssi: -45, security: 'WPA2' },
                { ssid: 'Guest-Network', bssid: '12:34:56:78:9A:BD', channel: 6, rssi: -60, security: 'Open' },
                { ssid: 'TP-Link_5GHz', bssid: '12:34:56:78:9A:BE', channel: 36, rssi: -55, security: 'WPA2' },
                { ssid: 'NETGEAR-123', bssid: '12:34:56:78:9A:BF', channel: 11, rssi: -70, security: 'WPA/WPA2' }
            ];
            
            networks.forEach(net => {
                const row = document.createElement('tr');
                row.innerHTML = `
                    <td>${net.ssid}</td>
                    <td>${net.bssid}</td>
                    <td>${net.channel}</td>
                    <td>${net.rssi} dBm</td>
                    <td>${net.security}</td>
                    <td>
                        <button class="action-btn"><i class="fas fa-ban"></i></button>
                        <button class="action-btn"><i class="fas fa-clone"></i></button>
                        <button class="action-btn"><i class="fas fa-key"></i></button>
                    </td>
                `;
                resultsBody.appendChild(row);
            });
            
            addLogEntry('[INFO] WiFi scan complete');
        }, 3000);
    } else {
        addLogEntry('[INFO] WiFi scan stopped');
    }
}

function simulateBLEScan(isStarting) {
    if (isStarting) {
        const resultsBody = document.getElementById('ble-results-body');
        resultsBody.innerHTML = '<tr><td colspan="5">Scanning...</td></tr>';
        
        addLogEntry('[INFO] Starting BLE scan');
        
        setTimeout(() => {
            resultsBody.innerHTML = '';
            
            // Create some sample devices
            const devices = [
                { name: 'iPhone 13', mac: '12:34:56:78:9A:BC', rssi: -45, manufacturer: 'Apple' },
                { name: 'Galaxy Watch', mac: '12:34:56:78:9A:BD', rssi: -60, manufacturer: 'Samsung' },
                { name: 'MI Band', mac: '12:34:56:78:9A:BE', rssi: -55, manufacturer: 'Xiaomi' }
            ];
            
            devices.forEach(dev => {
                const row = document.createElement('tr');
                row.innerHTML = `
                    <td>${dev.name}</td>
                    <td>${dev.mac}</td>
                    <td>${dev.rssi} dBm</td>
                    <td>${dev.manufacturer}</td>
                    <td>
                        <button class="action-btn"><i class="fas fa-info-circle"></i></button>
                    </td>
                `;
                resultsBody.appendChild(row);
            });
            
            addLogEntry('[INFO] BLE scan complete');
        }, 3000);
    } else {
        addLogEntry('[INFO] BLE scan stopped');
    }
}

function simulatePacketMonitor(isStarting) {
    const liveData = document.getElementById('live-data');
    
    if (isStarting) {
        liveData.innerHTML = '';
        addLogEntry('[INFO] Starting packet monitor');
        
        window.packetInterval = setInterval(() => {
            const packetTypes = ['Beacon', 'Probe Request', 'Data', 'ACK', 'RTS', 'CTS'];
            const type = packetTypes[Math.floor(Math.random() * packetTypes.length)];
            const mac = generateRandomMAC();
            
            const packetDiv = document.createElement('div');
            packetDiv.className = 'packet-item';
            packetDiv.innerHTML = `[${new Date().toLocaleTimeString()}] ${type} from ${mac}`;
            
            liveData.insertBefore(packetDiv, liveData.firstChild);
            
            // Limit number of entries to prevent memory issues
            if (liveData.children.length > 100) {
                liveData.removeChild(liveData.lastChild);
            }
        }, 500);
    } else {
        addLogEntry('[INFO] Packet monitor stopped');
        clearInterval(window.packetInterval);
    }
}

function simulateProbeSniffing(isStarting) {
    const liveData = document.getElementById('live-data');
    
    if (isStarting) {
        liveData.innerHTML = '';
        
        const hopping = document.getElementById('probe-hopping').checked;
        const channel = hopping ? 'All (hopping)' : document.getElementById('probe-channel').value;
        
        addLogEntry(`[INFO] Starting probe request sniffer on channel ${channel}`);
        
        window.probeInterval = setInterval(() => {
            const ssids = ['Home-WiFi', 'iPhone', 'AndroidAP', 'NETGEAR', 'Linksys', 'Free WiFi', 'Airport_WiFi'];
            const ssid = ssids[Math.floor(Math.random() * ssids.length)];
            const mac = generateRandomMAC();
            
            const probeDiv = document.createElement('div');
            probeDiv.className = 'packet-item mgmt';
            probeDiv.innerHTML = `[${new Date().toLocaleTimeString()}] Probe request for "${ssid}" from ${mac}`;
            
            liveData.insertBefore(probeDiv, liveData.firstChild);
            
            if (liveData.children.length > 100) {
                liveData.removeChild(liveData.lastChild);
            }
        }, 1500);
    } else {
        addLogEntry('[INFO] Probe request sniffer stopped');
        clearInterval(window.probeInterval);
    }
}

function simulateHandshakeCapture(isStarting) {
    const liveData = document.getElementById('live-data');
    
    if (isStarting) {
        liveData.innerHTML = '';
        
        const ssid = document.getElementById('handshake-ssid').value || 'Target-Network';
        const channel = document.getElementById('handshake-channel').value;
        const autoDeauth = document.getElementById('handshake-deauth').checked;
        
        addLogEntry(`[INFO] Starting handshake capture for "${ssid}" on channel ${channel}`);
        
        if (autoDeauth) {
            addLogEntry(`[INFO] Auto deauthentication enabled`);
        }
        
        setTimeout(() => {
            addLogEntry(`[INFO] Listening for handshakes...`);
            
            if (autoDeauth) {
                setTimeout(() => {
                    const mac = generateRandomMAC();
                    
                    const deauthDiv = document.createElement('div');
                    deauthDiv.className = 'packet-item';
                    deauthDiv.innerHTML = `[${new Date().toLocaleTimeString()}] Sending deauth to client ${mac}`;
                    
                    liveData.insertBefore(deauthDiv, liveData.firstChild);
                    
                    setTimeout(() => {
                        const handshakeDiv = document.createElement('div');
                        handshakeDiv.className = 'packet-item';
                        handshakeDiv.style.color = '#4CAF50';
                        handshakeDiv.innerHTML = `[${new Date().toLocaleTimeString()}] <strong>HANDSHAKE CAPTURED for ${ssid}!</strong>`;
                        
                        liveData.insertBefore(handshakeDiv, liveData.firstChild);
                        
                        const saveDiv = document.createElement('div');
                        saveDiv.className = 'packet-item';
                        saveDiv.innerHTML = `[${new Date().toLocaleTimeString()}] Saved to handshake_${ssid}_${getCurrentDate()}.pcap`;
                        
                        liveData.insertBefore(saveDiv, liveData.firstChild);
                    }, 2000);
                }, 3000);
            }
        }, 1000);
    } else {
        addLogEntry('[INFO] Handshake capture stopped');
    }
}

// Helper functions
function addLogEntry(message) {
    const logElement = document.getElementById('system-log');
    
    if (logElement) {
        const entry = document.createElement('div');
        entry.className = 'log-entry';
        entry.textContent = message;
        
        logElement.insertBefore(entry, logElement.firstChild);
        
        // Limit log entries
        if (logElement.children.length > 100) {
            logElement.removeChild(logElement.lastChild);
        }
    }
}

function addLogToElement(element, message) {
    if (element) {
        const entry = document.createElement('div');
        entry.className = 'log-entry';
        entry.textContent = message;
        
        element.insertBefore(entry, element.firstChild);
        
        // Limit log entries
        if (element.children.length > 100) {
            element.removeChild(element.lastChild);
        }
    }
}

function generateRandomMAC() {
    const hexDigits = '0123456789ABCDEF';
    let mac = '';
    
    for (let i = 0; i < 6; i++) {
        const segment = hexDigits[Math.floor(Math.random() * 16)] + hexDigits[Math.floor(Math.random() * 16)];
        mac += segment + (i < 5 ? ':' : '');
    }
    
    return mac;
}

function simulateFirmwareUpdate() {
    addLogEntry('[INFO] Starting firmware update');
    addLogEntry('[INFO] Downloading firmware...');
    
    setTimeout(() => {
        addLogEntry('[INFO] Firmware downloaded');
        addLogEntry('[INFO] Verifying firmware...');
        
        setTimeout(() => {
            addLogEntry('[INFO] Firmware verified');
            addLogEntry('[INFO] Installing firmware...');
            
            setTimeout(() => {
                addLogEntry('[INFO] Firmware installed successfully');
                addLogEntry('[INFO] Restarting device...');
            }, 2000);
        }, 1500);
    }, 2000);
}

function simulateFactoryReset() {
    addLogEntry('[INFO] Factory reset initiated');
    addLogEntry('[INFO] Clearing all settings...');
    
    setTimeout(() => {
        addLogEntry('[INFO] Settings cleared');
        addLogEntry('[INFO] Restoring default configuration...');
        
        setTimeout(() => {
            addLogEntry('[INFO] Default configuration restored');
            addLogEntry('[INFO] Restarting device...');
        }, 1500);
    }, 1500);
}

function simulateRestart() {
    addLogEntry('[INFO] Restarting device...');
    
    setTimeout(() => {
        addLogEntry('[INFO] Device is shutting down');
        
        setTimeout(() => {
            window.location.reload();
        }, 2000);
    }, 1000);
}

function getCurrentDate() {
    const now = new Date();
    return now.getFullYear() + 
        String(now.getMonth() + 1).padStart(2, '0') + 
        String(now.getDate()).padStart(2, '0');
}

// Status updates
function startStatusUpdates() {
    // Update uptime
    let seconds = 0;
    
    setInterval(() => {
        seconds++;
        
        const hours = Math.floor(seconds / 3600).toString().padStart(2, '0');
        const minutes = Math.floor((seconds % 3600) / 60).toString().padStart(2, '0');
        const secs = (seconds % 60).toString().padStart(2, '0');
        
        const uptimeElement = document.getElementById('uptime');
        if (uptimeElement) {
            uptimeElement.querySelector('span').textContent = `Uptime: ${hours}:${minutes}:${secs}`;
        }
    }, 1000);
}

// Make utility functions globally accessible
window.selectForDeauth = function(bssid, ssid) {
    document.querySelector('[data-target="wifi-attacks"]').click();
    
    setTimeout(() => {
        document.getElementById('deauth-target').value = bssid;
        document.getElementById('deauth-mode').value = 'ssid';
    }, 300);
};

window.selectForEvilTwin = function(ssid, channel) {
    document.querySelector('[data-target="wifi-attacks"]').click();
    
    setTimeout(() => {
        document.getElementById('evil-twin-ssid').value = ssid;
        document.getElementById('evil-twin-channel').value = channel;
    }, 300);
};

window.selectForHandshake = function(ssid, channel) {
    document.querySelector('[data-target="sniffers"]').click();
    
    setTimeout(() => {
        document.getElementById('handshake-ssid').value = ssid;
        document.getElementById('handshake-channel').value = channel;
    }, 300);
};

function toggleBluetoothStatus(button) {
    if (button.textContent.includes('Toggle BLE')) {
        button.innerHTML = '<i class="fab fa-bluetooth"></i> BLE: ON';
        button.style.backgroundColor = '#4CAF50';
        addLogEntry('[INFO] Bluetooth enabled');
    } else {
        button.innerHTML = '<i class="fab fa-bluetooth"></i> Toggle BLE';
        button.style.backgroundColor = '';
        addLogEntry('[INFO] Bluetooth disabled');
    }
  }
// --- PASTE ALL YOUR script.js CONTENT HERE ---

R"rawcanvas(
    </script>
</body>
</html>
)rawcanvas";

#endif
