#ifndef WEB_CONTENT_H
#define WEB_CONTENT_H

const char index_html[] PROGMEM = R"rawcanvas(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Marauder Headless Controller</title>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.15.4/css/all.min.css">
    <style>
        :root {
            --primary-color: #2196F3; --secondary-color: #03A9F4; --danger-color: #F44336;
            --warning-color: #FFC107; --success-color: #4CAF50; --text-color: #333;
            --background-color: #f5f5f5; --card-bg: #fff; --border-color: #ddd;
            --header-bg: #1976D2; --header-text: #fff; --shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
            --firmware-color: #ff9800; --spiffs-color: #03a9f4; --free-color: #4caf50;
        }
        body.dark-mode {
            --text-color: #f0f0f0; --background-color: #121212; --card-bg: #1e1e1e;
            --border-color: #333; --header-bg: #0d47a1; --shadow: 0 2px 4px rgba(0, 0, 0, 0.3);
        }
        * { box-sizing: border-box; margin: 0; padding: 0; }
        body { font-family: 'Segoe UI', Tahoma, sans-serif; background-color: var(--background-color); color: var(--text-color); line-height: 1.6; }
        header { background-color: var(--header-bg); color: var(--header-text); padding: 1rem; box-shadow: var(--shadow); }
        .status-bar { display: flex; flex-wrap: wrap; margin-top: 10px; font-size: 0.9rem; }
        .status-item { margin-right: 20px; display: flex; align-items: center; }
        nav { background-color: var(--card-bg); box-shadow: var(--shadow); }
        nav ul { display: flex; list-style: none; overflow-x: auto; padding: 0; }
        .nav-item { padding: 15px 20px; cursor: pointer; white-space: nowrap; border-bottom: 3px solid transparent; }
        .nav-item.active { color: var(--primary-color); border-bottom: 3px solid var(--primary-color); font-weight: bold; }
        main { padding: 20px 10px; }
        .content-section { display: none; }
        .content-section.active { display: block; }
        .card { background-color: var(--card-bg); border-radius: 5px; box-shadow: var(--shadow); margin-bottom: 20px; padding: 15px; }
        .log-container { background-color: #1e1e1e; color: #f0f0f0; height: 300px; overflow-y: auto; padding: 10px; font-family: monospace; border-radius: 4px; }
        button { padding: 8px 15px; border: none; border-radius: 4px; cursor: pointer; background: var(--primary-color); color: white; margin: 5px; }
        .results-table { width: 100%; border-collapse: collapse; }
        .results-table th, .results-table td { padding: 10px; border-bottom: 1px solid var(--border-color); text-align: left; }
    </style>
</head>
<body>
    <div class="container">
        <header>
            <h1><i class="fas fa-wifi"></i> ESP32 Marauder</h1>
            <div class="status-bar">
                <div class="status-item"><i class="fas fa-clock"></i> <span id="uptime-display">00:00:00</span></div>
                <div class="status-item"><i class="fas fa-memory"></i> <span>Free: 115 KB</span></div>
            </div>
        </header>

        <nav>
            <ul>
                <li class="nav-item active" onclick="show('dashboard')">Dashboard</li>
                <li class="nav-item" onclick="show('wifi-attacks')">WiFi Attacks</li>
                <li class="nav-item" onclick="show('scanners')">Scanners</li>
                <li class="nav-item" onclick="show('sniffers')">Sniffers</li>
                <li class="nav-item" onclick="show('settings')">Settings</li>
            </ul>
        </nav>

        <main>
            <section id="dashboard" class="content-section active">
                <div class="card">
                    <h3>Quick Actions</h3>
                    <button onclick="show('scanners')">Scan Networks</button>
                    <button id="toggle-ble-btn" onclick="toggleBLE(this)">Toggle BLE</button>
                </div>
                <div class="card">
                    <h3>System Log</h3>
                    <div id="system-log" class="log-container"></div>
                    <button onclick="document.getElementById('system-log').innerHTML=''">Clear Log</button>
                </div>
            </section>

            <section id="wifi-attacks" class="content-section">
                <div class="card">
                    <h3>Deauth Attack</h3>
                    <input type="text" id="deauth-target" placeholder="Target MAC">
                    <button onclick="addLogEntry('Deauth Started')">Start Deauth</button>
                </div>
            </section>

            <section id="scanners" class="content-section">
                <div class="card">
                    <h3>WiFi Scanner</h3>
                    <button onclick="simulateWiFiScan()">Start WiFi Scan</button>
                    <table class="results-table">
                        <thead><tr><th>SSID</th><th>BSSID</th><th>CH</th><th>RSSI</th></tr></thead>
                        <tbody id="wifi-results"></tbody>
                    </table>
                </div>
            </section>

            <section id="sniffers" class="content-section">
                <div class="card">
                    <h3>Packet Monitor</h3>
                    <button onclick="addLogEntry('Sniffing started...')">Start Sniffer</button>
                </div>
            </section>

            <section id="settings" class="content-section">
                <div class="card">
                    <h3>Interface</h3>
                    <label><input type="checkbox" onchange="document.body.classList.toggle('dark-mode')"> Dark Mode</label>
                </div>
            </section>
        </main>
    </div>

    <script>
        function show(id) {
            document.querySelectorAll(".content-section").forEach(s => s.classList.remove("active"));
            document.querySelectorAll(".nav-item").forEach(n => n.classList.remove("active"));
            document.getElementById(id).classList.add("active");
            event.target.classList.add("active");
        }

        function addLogEntry(msg) {
            const log = document.getElementById("system-log");
            const entry = document.createElement("div");
            entry.textContent = "[" + new Date().toLocaleTimeString() + "] " + msg;
            log.insertBefore(entry, log.firstChild);
        }

        function toggleBLE(btn) {
            if (btn.textContent.includes("Toggle BLE")) {
                btn.innerHTML = "<i class='fab fa-bluetooth'></i> BLE: ON";
                btn.style.backgroundColor = "#4CAF50";
                addLogEntry("Bluetooth Enabled");
            } else {
                btn.innerHTML = "<i class='fab fa-bluetooth'></i> Toggle BLE";
                btn.style.backgroundColor = "";
                addLogEntry("Bluetooth Disabled");
            }
        }

        function simulateWiFiScan() {
            const tbody = document.getElementById("wifi-results");
            tbody.innerHTML = "<tr><td colspan='4'>Scanning...</td></tr>";
            setTimeout(() => {
                tbody.innerHTML = "<tr><td>Home_WiFi</td><td>12:34:56:78</td><td>1</td><td>-45dBm</td></tr>";
                addLogEntry("WiFi Scan Complete");
            }, 2000);
        }

        let sec = 0;
        setInterval(() => {
            sec++;
            let h = Math.floor(sec/3600).toString().padStart(2, "0");
            let m = Math.floor((sec%3600)/60).toString().padStart(2, "0");
            let s = (sec%60).toString().padStart(2, "0");
            document.getElementById("uptime-display").textContent = h + ":" + m + ":" + s;
        }, 1000);

        addLogEntry("Marauder Headless Ready");
    </script>
</body>
</html>
)rawcanvas";

#endif
