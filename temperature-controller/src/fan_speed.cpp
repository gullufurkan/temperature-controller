/*Fan Speed*/
#include "fan_speed.h"

/*	Set Fan Speed
 *	Fan speed adjusted according to diffence between set temperature and
 *room temperature. When the temperature difference decreases, fan speed also
 *decreases.
 */
void FanSpeed::setFanSpeed(eCurrentStatus currentStatus, int currentTemperature,
                           int setTemperature) {
  switch (currentStatus) {
  case eCurrentStatus::COOLING_IN_PROGRESS: /* FALLTHROUGH */
  case eCurrentStatus::HEATING_IN_PROGRESS:
    if ((currentTemperature <
         setTemperature +
             static_cast<int>(eFanSpeedTemperatureRange::eFAN_TEMP_LOW)) &&
        (currentTemperature >
         setTemperature -
             static_cast<int>(eFanSpeedTemperatureRange::eFAN_TEMP_LOW))) {
      fanSpeed = eFanSpeedSettings::eFAN_SPEED_LOW;
    } else if ((currentTemperature <
                setTemperature +
                    static_cast<int>(
                        eFanSpeedTemperatureRange::eFAN_TEMP_MID)) &&
               (currentTemperature >
                setTemperature -
                    static_cast<int>(
                        eFanSpeedTemperatureRange::eFAN_TEMP_MID))) {
      fanSpeed = eFanSpeedSettings::eFAN_SPEED_MID;
    } else {
      fanSpeed = eFanSpeedSettings::eFAN_SPEED_HIGH;
    }
    break;

  case eCurrentStatus::SYSTEM_OFF:
    fanSpeed = eFanSpeedSettings::eFAN_SPEED_OFF;
    break;

  default:
    fanSpeed = eFanSpeedSettings::eFAN_SPEED_OFF;
  }
}

/*	Get Fan Speed	*/
eFanSpeedSettings FanSpeed::getFanSpeed(void) { return fanSpeed; }