#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>

#include "WiFiModule.h"
#include "HttpModule.h"
#include "MqttModule.h"

const char *ssid = "";      // Nombre de la red WiFi
const char *password = "";  // Contraseña de la red WiFi
const char *server = "";    // Dirección IP del servidor HTTP
const int http_port = 0;    // Puerto del servidor HTTP
const int mqtt_port = 8310; // Puerto del Broker MQTT

WiFiClient esp32Client;
PubSubClient mqttClient(esp32Client);

void setup()
{
  Serial.begin(115200);
  WiFiModule::conectarWiFi(ssid, password);
  mqttClient.setServer(server, mqtt_port);
  mqttClient.setCallback(MqttModule::callback);
}
void loop()
{
  if (!mqttClient.connected())
  {
    MqttModule::conectarMQTT(mqttClient, server, mqtt_port, "smartgrow");
  }
  mqttClient.loop();
}