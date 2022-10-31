#include "temperature_controller.h"
#include <iostream>
#include <memory>

using namespace std;

using namespace std;

int main() {
  unique_ptr<TemperatureSensor> pTemperatureSensor =
      make_unique<TemperatureSensor>();
  unique_ptr<FanSpeed> pFanSpeed = make_unique<FanSpeed>();

  TemperatureController homeTempController(move(pFanSpeed),
                                           move(pTemperatureSensor));

  while (true) {
    homeTempController.mainController();
  }
}