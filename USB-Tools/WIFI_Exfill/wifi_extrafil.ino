/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com/esp8266-nodemcu-access-point-ap-web-server/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

// netsh wlan set hostednetwork mode=allow ssid="ESP8266-Access-Point" key=123456789
// default ip address of server is 192.168.4.1

// Import required libraries
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "FS.h"

const char* ssid     = "LingZhiGei_Wifi";
const char* password = "12345678";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
  <h2>ESP8266 DHT Server</h2>
</body>
</html>)rawliteral";

String storage1;
String storage2;
String storage3;

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);


  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });
  server.on("/login", HTTP_GET, [](AsyncWebServerRequest *request){
    storage1 = request->getParam("password")->value();
    request->send(200, "text/html", "OK");
  });
  server.on("/show", HTTP_GET, [](AsyncWebServerRequest *request){
    storage2 = request->getParam("file")->value();
    request->send(200, "text/html", "OK");
  });
  server.on("/check", HTTP_GET, [](AsyncWebServerRequest *request){
    storage3 = request->getParam("hash")->value();
    request->send(200, "text/html", "OK");
  });
  server.on("/storage1", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", storage1);
  });
  server.on("/storage2", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", storage2);
  });
  server.on("/storage3", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", storage3);
  });
  // Start server
  server.begin();
}
 
void loop(){
}

