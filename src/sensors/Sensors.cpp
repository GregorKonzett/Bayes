#include "Sensors.hpp"

Sensors::Sensors(uint8_t bmp_address, uint8_t bno_address, float seaLevelhPa)
{
    _bmp_address = bmp_address;
    _bno_address = bno_address;
    _seaLevelhPa = seaLevelhPa;
}

void Sensors::begin()
{
    _bno = Adafruit_BNO055(55, _bno_address);
    _bmp = Adafruit_BMP280();
    while (!_bno.begin() || !_bmp.begin(_bmp_address))
    {
        Serial.println("Init failed");
    }

    Serial.println("Init Completed");
}

void Sensors::print_data()
{
    sensor_data data = this->get_data();

    Serial.print(F("Temperature = "));
    Serial.print(data.temperature);
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(data.pressure);
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(data.altitude);
    Serial.println(" m");

    Serial.print("Roll: ");
    Serial.println(data.gyroscope.roll);
    Serial.print("Pitch: ");
    Serial.print(data.gyroscope.pitch);
    Serial.print("Heading: ");
    Serial.println(data.gyroscope.heading);
    Serial.println("-------");
}

sensor_data Sensors::get_data()
{
    sensor_data data;

    data.pressure = _bmp.readPressure();
    data.temperature = _bmp.readTemperature();
    data.altitude = _bmp.readAltitude(_seaLevelhPa);

    sensors_event_t gyroData, orientationData, accelerationData;

    _bno.getEvent(&gyroData, Adafruit_BNO055::VECTOR_GYROSCOPE);
    _bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
    _bno.getEvent(&accelerationData, Adafruit_BNO055::VECTOR_LINEARACCEL);

    data.gyroscope = gyroData.gyro;
    data.acceleration = accelerationData.acceleration;
    data.orientation = orientationData.orientation;

    return data;
}

void Sensors::setup_bmp()
{
    /* Default settings from datasheet. */
    _bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                     Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                     Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                     Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                     Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}