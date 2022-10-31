/*Temperature Controller*/
#include "temperature_controller.h"

/*	Main Controller
 *	Should be called periodically.
 *	Reads the current room temperature, controls fan speed.
 */
void TemperatureController::mainController(void) {
  getRoomTemperature();
  controlFan();
}

/*	Fan Controller
 *	Compares the current room temperature with desired temperature and sets
 *the state.
 */
void TemperatureController::controlFan(void) {
  switch (currentStatus) {
  case eCurrentStatus::COOLING_IN_PROGRESS:
    if (roomTemp <=
        (userSettings.setTemperature - DEFAULT_TEMPERATURE_HYSTERESIS)) {
      currentStatus = eCurrentStatus::HEATING_IN_PROGRESS;
    } else {
      currentStatus = eCurrentStatus::COOLING_IN_PROGRESS;
    }
    break;
  case eCurrentStatus::HEATING_IN_PROGRESS:
    if (roomTemp >=
        (userSettings.setTemperature + DEFAULT_TEMPERATURE_HYSTERESIS)) {
      currentStatus = eCurrentStatus::COOLING_IN_PROGRESS;
    } else {
      currentStatus = eCurrentStatus::HEATING_IN_PROGRESS;
    }
    break;

  case eCurrentStatus::SYSTEM_OFF:
    if (roomTemp > userSettings.setTemperature) {
      currentStatus = eCurrentStatus::COOLING_IN_PROGRESS;
    } else if (roomTemp < userSettings.setTemperature) {
      currentStatus = eCurrentStatus::HEATING_IN_PROGRESS;
    } else {
      currentStatus = eCurrentStatus::SYSTEM_OFF;
    }
    break;

  default:
    if (roomTemp > userSettings.setTemperature) {
      currentStatus = eCurrentStatus::COOLING_IN_PROGRESS;
    } else if (roomTemp < userSettings.setTemperature) {
      currentStatus = eCurrentStatus::HEATING_IN_PROGRESS;
    } else {
      currentStatus = eCurrentStatus::SYSTEM_OFF;
    }
  }

  upFan->setFanSpeed(currentStatus, roomTemp, userSettings.setTemperature);
}

/*	Set Set Temperature
 *	Checks the temperature coming from the user according to limits and sets
 *it.
 */
void TemperatureController::setSetTemperature(int temp) {
  if (temp > MAX_TEMPERATURE) {
    userSettings.setTemperature = MAX_TEMPERATURE;
  } else if (temp < MIN_TEMPERATURE) {
    userSettings.setTemperature = MIN_TEMPERATURE;
  } else {
    userSettings.setTemperature = temp;
  }
}

/*	Get Set Temperature
 *	Returns the desired temperature coming from the user.
 */
int TemperatureController::getSetTemperature(void) {
  return userSettings.setTemperature;
}

/*	Get Room Temperature
 *	Reads the temperature sensor.
 */
void TemperatureController::getRoomTemperature(void) {
  roomTemp = upSensor->readSensor();
}

/*	Get Current Status
 *	Returns the current status of system.
 */
eCurrentStatus TemperatureController::getCurrentStatus(void) {
  return currentStatus;
}