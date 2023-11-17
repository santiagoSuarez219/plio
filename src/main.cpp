#include <Arduino.h>
#include <Wire.h>
#include <ArduinoJson.h>

#include "WifiModule.h"
#include "HttpModule.h"
#include "SCD40Sensor.h"

const char *ssid = "";     // Nombre de la red WiFi
const char *password = ""; // Contraseña de la red WiFi
const char *server = "";   // Dirección IP del servidor HTTP
const int http_port = 0;   // Puerto del servidor HTTP
const char *id_sensor = "650dc7d640e0be7842fc4239";

WifiModule wifiModule(ssid, password);
HttpModule httpClient(server, http_port);
SCD40Sensor SCD40(id_sensor);

const unsigned long interval = 60000;
unsigned long previousMillis = 0;

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  wifiModule.conectarWifi();
}
void loop()
{
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    SCD40.read();
    StaticJsonDocument<200> jsonDocument;
    jsonDocument["co2"] = *SCD40.getCo2();
    jsonDocument["temperatura"] = *SCD40.getTemperatura();
    jsonDocument["humedad"] = *SCD40.getHumedad();
    jsonDocument["VPD"] = *SCD40.getVPD();
    jsonDocument["sensor"] = SCD40.getId();
    String jsonString;
    serializeJson(jsonDocument, jsonString);
    httpClient.enviarDatosHTTP(jsonString.c_str(), "scd40");
    delay(1000);
  }
}