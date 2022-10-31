#ifndef TEMPERATURE_CONTROLLER_H
#define TEMPERATURE_CONTROLLER_H

#include "fan_speed.h"
#include "machine.h"
#include "temperature_sensor.h"
#include <iostream>
#include <memory>


using namespace std;

struct stUserSettings {
  int setTemperature;
  uint16_t temperatureHysteresis;
};

class TemperatureController {
public:
  // Default Constructor
  TemperatureController(unique_ptr<FanSpeed> upFanSpeed,
                        unique_ptr<TemperatureSensor> upTemperatureSensor)
      : upFan(move(upFanSpeed)), upSensor(move(upTemperatureSensor)) {
    userSettings.setTemperature = DEFAULT_TEMPERATURE;
    userSettings.temperatureHysteresis = DEFAULT_TEMPERATURE_HYSTERESIS;
  }

  // Destructor
  virtual ~TemperatureController() { ; }

  /**
   * @brief: Main Controller Algorithm
   * @param:
   * @return:
   */
  virtual void mainController(void);

  /**
   * @brief: Compare temperature of room and set temperature and control fan
   * @param:
   * @return:
   */
  virtual void controlFan(void);

  /**
   * @brief: Set Set Temperature from the user
   * @param: temp (Desired temperature coming from the user)
   * @return:
   */
  virtual void setSetTemperature(int temp);

  /**
   * @brief: Get Set Temperature from the user
   * @param:
   * @return:  Desired temperature of user
   */
  virtual int getSetTemperature(void);

  /**
   * @brief: Get Room Temperature from the sensor
   * @param:
   * @return:
   */
  virtual void getRoomTemperature(void);

  /**
   * @brief: Get Status
   * @param:
   * @return:  Status (Heating, Cooling or OFF)
   */
  virtual eCurrentStatus getCurrentStatus(void);

private:
  stUserSettings userSettings;
  unique_ptr<FanSpeed> upFan;
  unique_ptr<TemperatureSensor> upSensor;
  int roomTemp;
  eCurrentStatus currentStatus;

protected:
};

#endif /* TEMPERATURE_CONTROLLER_H */