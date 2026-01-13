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