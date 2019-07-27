//************************//
// Robomow RX12u WiFi     //
//************************//

//Includes
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>  //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

//Global variables
#define GoPin 3
#define StopPin 4
#define WEBSRVPORT 80
bool running = false;
//Fallback WiFi AP credentials
char wifiap[] = "Meow";
char wifipw[] = "RobiTheMower01";

//Other global things
ESP8266WebServer server(WEBSRVPORT);

//Press a button for x ms
void pressButton(bool go) {
  if (go) {
    Serial.println("Go go go!");
    digitalWrite(GoPin, HIGH);
    delay(600);
    digitalWrite(GoPin, LOW);
  } else {
    Serial.println("Stopping. Narf.");
    digitalWrite(StopPin, HIGH);
    delay(600);
    digitalWrite(StopPin, LOW);
  }
}

//Webserver Events
void EventIndex() {
  if (server.args() > 0) {
    if (server.arg("pressStart") == "1") {
      pressButton(true);
      server.sendHeader("Cache-Control", "no-cache");
      server.send(200, "text/plain", "pressedStart");
    } else if (server.arg("pressStop") == "1") {
      pressButton(false);
      server.sendHeader("Cache-Control", "no-cache");
      server.send(200, "text/plain", "pressedStop");
    } else {
      server.sendHeader("Cache-Control", "no-cache");
      server.send(200, "text/plain", "Please use one of the following parameters: ?pressStart=1 or ?pressStop=1");
    }
  } else {
      server.sendHeader("Cache-Control", "no-cache");
      server.send(200, "text/plain", "Please use one of the following parameters: ?pressStart=1 or ?pressStop=1");
  }
}

void EventNotFound() {
  server.send(404, "text/plan", "404: Not found");
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  Serial.begin(115200);
  pinMode(GoPin, OUTPUT);
  pinMode(StopPin, OUTPUT);
  digitalWrite(GoPin, LOW);
  digitalWrite(StopPin, LOW);
  WiFiManager wifiManager;
  //wifiManager.resetSettings(); //reset WiFi settings
  wifiManager.autoConnect(wifiap, wifipw);
  Serial.println("Connected...starting Webserver");
  digitalWrite(LED_BUILTIN, HIGH);
  server.on("/", EventIndex);
  server.onNotFound(EventNotFound);
  server.begin();
  Serial.println("ESP-Startup complete.");
}

void loop() {
  server.handleClient();
}
