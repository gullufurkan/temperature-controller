#ifndef FAN_SPEED_H
#define FAN_SPEED_H

#include "machine.h"
#include <iostream>


enum class eFanSpeedSettings {
  eFAN_SPEED_OFF = 0,
  eFAN_SPEED_LOW,
  eFAN_SPEED_MID,
  eFAN_SPEED_HIGH
};

enum class eFanSpeedTemperatureRange {
  eFAN_TEMP_STABILE = 0,
  eFAN_TEMP_LOW = 2,
  eFAN_TEMP_MID = 5,
  eFAN_TEMP_HIGH = 7
};

class FanSpeed {
public:
  // Default Constructor
  FanSpeed() { ; }

  // Destructor
  virtual ~FanSpeed() { ; }

  /**
   * @brief: Set Fan Speed
   * @param: currentStatus (Heating, Cooling or OFF)
   * @param: currentTemperature (Current value of room temperature)
   * @param: setTemperature (Desired temperature)
   * @return:
   */
  virtual void setFanSpeed(eCurrentStatus currentStatus, int currentTemperature,
                           int setTemperature);

  /**
   * @brief: Get Fan Speed feedback
   * @param:
   * @return: Fan Speed feedback from motor
   */
  virtual eFanSpeedSettings getFanSpeed(void);

private:
  eFanSpeedSettings fanSpeed;

protected:
};

#endif /* FAN_SPEED_H */