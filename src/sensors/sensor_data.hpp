#ifndef SENSOR_DATA_H
#define SENSORS_DATA_H

#include <Adafruit_Sensor.h>

struct sensor_data
{
    float temperature;
    float pressure;
    float altitude;
    sensors_vec_t gyroscope;
    sensors_vec_t acceleration;
    sensors_vec_t orientation;
};

#endif