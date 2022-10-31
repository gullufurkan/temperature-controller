#ifndef MOCK_FAN_SPEED_H
#define MOCK_FAN_SPEED_H

#include "../src/fan_speed.h"
#include "gmock/gmock.h"
#include <iostream>
#include <memory>


using namespace std;

class MockFanSpeed : public FanSpeed {
public:
  // MOCK_METHOD(void, setFanSpeed, (eCurrentStatus, int, int));
  // MOCK_METHOD(eFanSpeedSettings, getFanSpeed, ());

private:
protected:
};

#endif /* MOCK_FAN_SPEED_H */