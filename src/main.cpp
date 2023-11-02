#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <Wire.h>

#include "WiFiModule.h"
#include "HttpModule.h"
#include "MLX90640_API.h"
#include "MLX90640_I2C_Driver.h"

const char *ssid = ""; // Nombre de la red WiFi
const char *password = ""; // Contraseña de la red WiFi
const char* server = ""; // Dirección IP del servidor HTTP
const int http_port = 0; // Puerto del servidor HTTP 

const byte MLX90640_address = 0x33;
#define TA_SHIFT 8

float mlx90640To[768];
paramsMLX90640 mlx90640;

const byte calcStart = 33;

WiFiClient esp32Client;

void setup()
{
  Wire.begin();
  Wire.setClock(400000);
  Serial.begin(115200);
  WiFiModule::conectarWiFi(ssid, password);
  int status;
  uint16_t eeMLX90640[832];
  status = MLX90640_DumpEE(MLX90640_address, eeMLX90640);
  if (status != 0)
    Serial.println("Failed to load system parameters");

  status = MLX90640_ExtractParameters(eeMLX90640, &mlx90640);
  if (status != 0)
    Serial.println("Parameter extraction failed");

  MLX90640_SetRefreshRate(MLX90640_address, 0x04);
  Wire.setClock(1000000);
}

void loop()
{
  for (byte x = 0 ; x < 2 ; x++)
  {
    uint16_t mlx90640Frame[834];
    int status = MLX90640_GetFrameData(MLX90640_address, mlx90640Frame);

    float vdd = MLX90640_GetVdd(mlx90640Frame, &mlx90640);
    float Ta = MLX90640_GetTa(mlx90640Frame, &mlx90640);

    float tr = Ta - TA_SHIFT; //Reflected temperature based on the sensor ambient temperature
    float emissivity = 0.95;

    MLX90640_CalculateTo(mlx90640Frame, &mlx90640, emissivity, tr, mlx90640To);
  }

  for (int x = 0 ; x < 768 ; x++)
  {
    Serial.print(mlx90640To[x], 2);
    Serial.print(",");
  }
  Serial.println("");
}