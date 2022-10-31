/*Temperature Sensor*/
#include "temperature_sensor.h"

/*	Init Sensor
 *	Init sequence of sensor
 */
bool TemperatureSensor::initSensor(void) {
  bool status = false;

  // Init sensor according to configuration
  status = true;

  return status;
}

/*	Set Sensor
 *	Manipulate reading of temperature sensor for tests
 */
void TemperatureSensor::setSensor(int setVal) { temperatureVal = setVal; }

/*	Read Sensor
 *	Reads the raw ADC value coming from the sensor and converts it to
 *temperature.
 */
int TemperatureSensor::readSensor(void) { return temperatureVal; }