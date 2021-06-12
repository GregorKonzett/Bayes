#ifndef SENSORS_H
#define SENSORS_H

#include "Arduino.h"
#include "sensor_data.hpp"
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_BNO055.h>

class Sensors
{
public:
    Sensors(uint8_t bmp_address, uint8_t bno_address, float seaLevelhPa);
    void begin();
    void print_data();
    sensor_data get_data();

private:
    uint8_t _bmp_address;
    uint8_t _bno_address;
    float _seaLevelhPa;
    Adafruit_BMP280 _bmp;
    Adafruit_BNO055 _bno;

    void setup_bmp();
};

#endif
