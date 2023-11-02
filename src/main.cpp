#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>

#include "WiFiModule.h"
#include "HttpModule.h"

const char *ssid = ""; // Nombre de la red WiFi
const char *password = ""; // Contraseña de la red WiFi
const char* server = ""; // Dirección IP del servidor HTTP
const int http_port = 0; // Puerto del servidor HTTP 

WiFiClient esp32Client;

void setup()
{
  Serial.begin(115200);
  WiFiModule::conectarWiFi(ssid, password);
}
void loop()
{
}