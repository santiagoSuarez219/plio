#ifndef SCD40Sensor_h
#define SCD40Sensor_h

#include <Arduino.h>

class SCD40Sensor {
    public:
        SCD40Sensor(const char* id);
        void read();
        const float* getTemperatura() const;
        const float* getHumedad() const;
        const float* getCo2() const;
        const float* getVPD() const;
        const char* getId() const;
    private:
        const char* id;
        float temperatura;
        float humedad;
        float co2;
        float VPD;
        float calcularVPD(float temperatura, float humedad);
};

#endif