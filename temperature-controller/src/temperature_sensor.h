#ifndef TEMPERATURE_SENSOR_H
#define TEMPERATURE_SENSOR_H

#include <iostream>

class TemperatureSensor {
public:
  // Default Constructor
  TemperatureSensor() { ; }

  // Destructor
  ~TemperatureSensor() { ; }

  /**
   * @brief: Initialization of Sensor
   * @param:
   * @return: status (Success, Fail)
   */
  virtual bool initSensor(void);

  /**
   * @brief: Set sensor reading to manipulate data for tests
   * @param: setVal (desired value coming from the user)
   * @return: 
   */
  virtual void setSensor(int setVal);

  /**
   * @brief: Reading of Sensor
   * @param:
   * @return: Temperature value coming from the sensor
   */
  virtual int readSensor(void);

private:
  int temperatureVal;
protected:
};

#endif /* TEMPERATURE_SENSOR_H */