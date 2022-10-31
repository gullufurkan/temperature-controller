#include "../src/machine.h"
#include "../src/temperature_controller.h"
#include "../test/mock_fan_speed.h"
#include "../test/mock_temperature_sensor.h"
#include "gtest/gtest.h"

/*	Set Temperature
 *	Desired temperature coming from the user is controlled.
 */
TEST(Air_Conditioner_Test,
     WhenSetTemperatureIsBetweenMaxAndMin_ThenReturnDesiredTemperature) {
  unique_ptr<MockTemperatureSensor> mockSensor =
      make_unique<MockTemperatureSensor>();
  unique_ptr<MockFanSpeed> mockFan = make_unique<MockFanSpeed>();
  auto pFanSpeed = mockFan.get();

  TemperatureController homeTempController(move(mockFan), move(mockSensor));

  int userTemp = 0;

  // Check normal conditions
  homeTempController.setSetTemperature(25);
  userTemp = homeTempController.getSetTemperature();
  EXPECT_EQ(25, userTemp);

  homeTempController.setSetTemperature(0);
  userTemp = homeTempController.getSetTemperature();
  EXPECT_EQ(0, userTemp);

  homeTempController.setSetTemperature(-15);
  userTemp = homeTempController.getSetTemperature();
  EXPECT_EQ(-15, userTemp);
}

TEST(Air_Conditioner_Test, WhenSetTemperatureAboveMax_ThenReturnMax) {
  unique_ptr<MockTemperatureSensor> mockSensor =
      make_unique<MockTemperatureSensor>();
  unique_ptr<MockFanSpeed> mockFan = make_unique<MockFanSpeed>();
  auto pFanSpeed = mockFan.get();

  TemperatureController homeTempController(move(mockFan), move(mockSensor));

  int userTemp = 0;

  // Check above max
  homeTempController.setSetTemperature(150);
  userTemp = homeTempController.getSetTemperature();
  EXPECT_EQ(MAX_TEMPERATURE, userTemp);
}

TEST(Air_Conditioner_Test, WhenSetTemperatureBelowMin_ThenReturnMin) {
  unique_ptr<MockTemperatureSensor> mockSensor =
      make_unique<MockTemperatureSensor>();
  unique_ptr<MockFanSpeed> mockFan = make_unique<MockFanSpeed>();
  auto pFanSpeed = mockFan.get();

  TemperatureController homeTempController(move(mockFan), move(mockSensor));

  int userTemp = 0;

  // Check below min
  homeTempController.setSetTemperature(-75);
  userTemp = homeTempController.getSetTemperature();
  EXPECT_EQ(MIN_TEMPERATURE, userTemp);
}

/*	Status Control & Fan Speed Control
 *	Since sensor implementation does not exist
 *	Fixed room temperature are read from sensor as 25
 *	Desired temperature changes
 *	Random tests are conducted.
 */
TEST(Air_Conditioner_Test,
     WhenSetTemperatureEqualsRoomTemperature_ThenReturnSystemOff) {
  unique_ptr<MockTemperatureSensor> mockSensor =
      make_unique<MockTemperatureSensor>();
  auto pSensor = mockSensor.get();
  unique_ptr<MockFanSpeed> mockFan = make_unique<MockFanSpeed>();
  auto pFanSpeed = mockFan.get();

  TemperatureController homeTempController(move(mockFan), move(mockSensor));

  eFanSpeedSettings readFanSpeed = eFanSpeedSettings::eFAN_SPEED_OFF;
  eCurrentStatus currentStatus = eCurrentStatus::SYSTEM_OFF;

  pSensor->setSensor(25);
  
  // Check normal conditions
  homeTempController.setSetTemperature(25);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_OFF, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::SYSTEM_OFF, currentStatus);
}

TEST(Air_Conditioner_Test,
     WhenSetTemperatureHigherThanRoomTemperature_ThenReturnHeating) {
  unique_ptr<MockTemperatureSensor> mockSensor =
      make_unique<MockTemperatureSensor>();
  auto pSensor = mockSensor.get();
  unique_ptr<MockFanSpeed> mockFan = make_unique<MockFanSpeed>();
  auto pFanSpeed = mockFan.get();

  TemperatureController homeTempController(move(mockFan), move(mockSensor));

  eFanSpeedSettings readFanSpeed = eFanSpeedSettings::eFAN_SPEED_OFF;
  eCurrentStatus currentStatus = eCurrentStatus::SYSTEM_OFF;

  pSensor->setSensor(25);
  
  // Check normal conditions
  homeTempController.setSetTemperature(25);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_OFF, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::SYSTEM_OFF, currentStatus);

  homeTempController.setSetTemperature(26);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_LOW, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::HEATING_IN_PROGRESS, currentStatus);

  homeTempController.setSetTemperature(29);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_MID, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::HEATING_IN_PROGRESS, currentStatus);

  // Check above max
  homeTempController.setSetTemperature(150);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_HIGH, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::HEATING_IN_PROGRESS, currentStatus);
}

TEST(Air_Conditioner_Test,
     WhenSetTemperatureLowerThanRoomTemperature_ThenReturnCooling) {
  unique_ptr<MockTemperatureSensor> mockSensor =
      make_unique<MockTemperatureSensor>();
  auto pSensor = mockSensor.get();
  unique_ptr<MockFanSpeed> mockFan = make_unique<MockFanSpeed>();
  auto pFanSpeed = mockFan.get();

  TemperatureController homeTempController(move(mockFan), move(mockSensor));

  eFanSpeedSettings readFanSpeed = eFanSpeedSettings::eFAN_SPEED_OFF;
  eCurrentStatus currentStatus = eCurrentStatus::SYSTEM_OFF;

  pSensor->setSensor(25);
  
  // Check normal conditions
  homeTempController.setSetTemperature(25);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_OFF, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::SYSTEM_OFF, currentStatus);

  homeTempController.setSetTemperature(0);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_HIGH, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);

  // Check minus
  homeTempController.setSetTemperature(-45);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_HIGH, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);
}

/*	Status Control & Fan Speed Control
 *	Since sensor implementation does not exist
 *	Room temperature set by tester
 *	Constant desired temperature
 *	Random tests are conducted.
 */
TEST(Air_Conditioner_Test,
     WhenRoomTemperatureIncreasedContinuosly_ThenReturnCooling) {
  unique_ptr<MockTemperatureSensor> mockSensor =
      make_unique<MockTemperatureSensor>();
  auto pSensor = mockSensor.get();
  unique_ptr<MockFanSpeed> mockFan = make_unique<MockFanSpeed>();
  auto pFanSpeed = mockFan.get();

  TemperatureController homeTempController(move(mockFan), move(mockSensor));

  eFanSpeedSettings readFanSpeed = eFanSpeedSettings::eFAN_SPEED_OFF;
  eCurrentStatus currentStatus = eCurrentStatus::SYSTEM_OFF;

  // Random tests with fixed set temperature and changing room temperature
  homeTempController.setSetTemperature(25);

  // Case 1
  pSensor->setSensor(25);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_OFF, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::SYSTEM_OFF, currentStatus);

  // Case 2
  pSensor->setSensor(26);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_LOW, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);

  // Case 3
  pSensor->setSensor(27);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_MID, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);

  // Case 4
  pSensor->setSensor(30);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_HIGH, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);
}

TEST(Air_Conditioner_Test,
     WhenRoomTemperatureDecreasedContinuosly_ThenReturnHeating) {
  unique_ptr<MockTemperatureSensor> mockSensor =
      make_unique<MockTemperatureSensor>();
  auto pSensor = mockSensor.get();
  unique_ptr<MockFanSpeed> mockFan = make_unique<MockFanSpeed>();
  auto pFanSpeed = mockFan.get();

  TemperatureController homeTempController(move(mockFan), move(mockSensor));

  eFanSpeedSettings readFanSpeed = eFanSpeedSettings::eFAN_SPEED_OFF;
  eCurrentStatus currentStatus = eCurrentStatus::SYSTEM_OFF;

  // Random tests with fixed set temperature and changing room temperature
  homeTempController.setSetTemperature(25);

  // Case 1
  pSensor->setSensor(25);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_OFF, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::SYSTEM_OFF, currentStatus);

  // Case 2
  pSensor->setSensor(24);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_LOW, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::HEATING_IN_PROGRESS, currentStatus);

  // Case 3
  pSensor->setSensor(23);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_MID, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::HEATING_IN_PROGRESS, currentStatus);

  // Case 4
  pSensor->setSensor(20);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_HIGH, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::HEATING_IN_PROGRESS, currentStatus);
}

/*	Status Control & Fan Speed Control
 *	Since sensor implementation does not exist
 *	Room temperature set by tester
 *	Constant desired temperature
 *	Checks system status in case of temperature fluctuations around desired
 *temperature. Random tests are conducted.
 */
TEST(Air_Conditioner_Test, WhenRoomTemperatureChangesRandomly_ThenCheckStatus) {
  unique_ptr<MockTemperatureSensor> mockSensor =
      make_unique<MockTemperatureSensor>();
  auto pSensor = mockSensor.get();
  unique_ptr<MockFanSpeed> mockFan = make_unique<MockFanSpeed>();
  auto pFanSpeed = mockFan.get();

  TemperatureController homeTempController(move(mockFan), move(mockSensor));

  eFanSpeedSettings readFanSpeed = eFanSpeedSettings::eFAN_SPEED_OFF;
  eCurrentStatus currentStatus = eCurrentStatus::SYSTEM_OFF;

  // Random tests with fixed set temperature and changing room temperature
  homeTempController.setSetTemperature(25);

  // Case 1
  pSensor->setSensor(25);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_OFF, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::SYSTEM_OFF, currentStatus);

  // Case 2
  pSensor->setSensor(26);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_LOW, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);

  // Case 3
  pSensor->setSensor(25);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_LOW, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);

  // Case 4
  pSensor->setSensor(24);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_LOW, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::HEATING_IN_PROGRESS, currentStatus);

  // Case 5
  pSensor->setSensor(25);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_LOW, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::HEATING_IN_PROGRESS, currentStatus);

  // Case 6
  pSensor->setSensor(26);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_LOW, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);

  // Case 7
  pSensor->setSensor(27);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_MID, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);

  // Case 8
  pSensor->setSensor(30);
  homeTempController.mainController();

  readFanSpeed = pFanSpeed->getFanSpeed();
  EXPECT_EQ(eFanSpeedSettings::eFAN_SPEED_HIGH, readFanSpeed);

  currentStatus = homeTempController.getCurrentStatus();
  EXPECT_EQ(eCurrentStatus::COOLING_IN_PROGRESS, currentStatus);
}