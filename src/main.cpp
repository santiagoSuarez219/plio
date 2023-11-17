#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>

#include "WifiModule.h"
#include "HttpModule.h"

const char *ssid = ""; // Nombre de la red WiFi
const char *password = ""; // Contraseña de la red WiFi
const char* server = ""; // Dirección IP del servidor HTTP
const int http_port = 0; // Puerto del servidor HTTP 

WiFiClient esp32Client;
WifiModule wifiModule(ssid, password);
HttpModule httpClient(server, http_port);

void setup()
{
  Serial.begin(115200);
  wifiModule.conectarWifi();
}
void loop()
{
}