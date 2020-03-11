#include <Servo.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>

#include <ESP8266WebServer.h>

ESP8266WiFiMulti wifi;
ESP8266WebServer server(80);

Servo catapult;
// 900 to 1900 is 90 deg ccw
// 500 to 2300 is 180 deg

void setup() {
  Serial.begin(115200);

  // LED off
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  catapult.attach(0);
  catapult.writeMicroseconds(1950);

  // try to connect to wifi
  wifi.addAP("BigTreesLodge", "0293d1c79b");
  wifi.addAP("YilingLaozu", "CraftyTricks9");
  wifi.addAP("Ideenwerk_Lichtental_2.4Ghz", "WebSpace4Tastic");

  int attempts = 15;
  while (attempts > 0 && wifi.run() != WL_CONNECTED) {
    attempts--;
    delay(500);
  }

  if (wifi.run() == WL_CONNECTED) {
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    blink(2);
  } else {
    Serial.println("Couldn't connect, starting local AP");
    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(IPAddress(192, 168, 0, 1), IPAddress(0, 0, 0, 0), IPAddress(255, 255, 255, 0));
// wifi_softap_set_dhcps_offer_option(OFFER_ROUTER, 0)
    if (WiFi.softAP("remotecontrolwarfare")) {
      Serial.print("Ready and listening at ");
      Serial.println(WiFi.softAPIP());
      blink(3);
    } else {
      Serial.println("Failed?");
      blink(5);
    }
  }
  MDNS.begin("catapult");

  server.onNotFound(handleGet);
  server.on("/", HTTP_POST, handlePost);

  // start web server
  server.begin();
}

void loop() {
  server.handleClient();
}

void handleGet() {
  server.send(200, "text/html", "<html><head><title>remote control warfare</title></head><body><form method=\"POST\"><button type=\"submit\" formaction=\"/\" style=\"background-color: red\">HIT ME</button></form></body></html>"); 
}

void handlePost() {
  digitalWrite(LED_BUILTIN, LOW);
  delay(700);
  catapult.writeMicroseconds(2300);
  delay(700);
  catapult.writeMicroseconds(950);
  server.send(200, "text/html", "ok");
  delay(2500);
  catapult.writeMicroseconds(1950);
  delay(700);
  digitalWrite(LED_BUILTIN, HIGH);
}

void blink(int times) {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  while (true) {
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
    digitalWrite(LED_BUILTIN, HIGH);
    if (--times == 0) {
      break;
    }
    delay(250);
  }
}
(rott) (gott)
shoot root
∞§¶•ªdigital∞§¶•ª
