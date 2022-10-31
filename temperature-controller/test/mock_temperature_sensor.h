#ifndef MOCK_TEMPERATURE_SENSOR_H
#define MOCK_TEMPERATURE_SENSOR_H

#include "../src/temperature_sensor.h"
#include "gmock/gmock.h"
#include <iostream>
#include <memory>


using namespace std;

class MockTemperatureSensor : public TemperatureSensor {
public:
  // MOCK_METHOD(int, readSensor, ());

private:
protected:
};

#endif /* MOCK_TEMPERATURE_SENSOR_H */