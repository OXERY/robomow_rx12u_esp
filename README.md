# Robomow RX12u WLAN
WiFi bzw. WLAN für den Robomow RX12u

# Arduino IDE
Boardverwalter in Einstellungen hinzufügen: `http://arduino.esp8266.com/stable/package_esp8266com_index.json`

Im Boardverwalter den `ESP8266` hinzufügen

Hierbei werden die benötigten ESP-Bibliotheken installiert.

Bibliothek `WiFiManager by tzapu` installieren

`Generic ESP8266 Board` auswählen und flashen

# Nach Installation
Der ESP8266 verbindet sich, sofern bereits konfiguriert, mit dem bekannten WLAN-Netzwerk.

Sollte keines konfiguriert sein, wird dank WiFiManager ein WLAN geöffnet, das automatisch die Credentials abfragt.

Mögliche Kommandos an den (einfachen) Webserver:

Mähen starten: `http://IPvomESP/?pressStart=1`

Mähen stoppen: `http://IPvomESP/?pressStop=1`