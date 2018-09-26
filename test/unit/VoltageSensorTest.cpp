#include <gtest/gtest.h>
#include "VoltageSensor.h"
#include "MockHardware.h"

class VoltageSensorTest : public ::testing::Test {
protected:

    VoltageSensor *sensor;
    MockHardware *hardware;

    virtual void SetUp() {
        hardware = new MockHardware();
        sensor = new VoltageSensor(hardware, 7, 0.0);
    }

    virtual void TearDown() {
        delete hardware;
        delete sensor;
    }
};

TEST_F(VoltageSensorTest, CreationWithPins) {
    EXPECT_EQ(hardware, sensor->getHardware());
    EXPECT_EQ(7, sensor->getPin());
    EXPECT_NEAR(0, sensor->getInterferenceAdjustment(), 0.01);
}

TEST_F(VoltageSensorTest, ReadingZeroVolts) {
    hardware->analogReads[7].push(0);
    EXPECT_DOUBLE_EQ(0, sensor->readVoltage());
}

TEST_F(VoltageSensorTest, Reading5Volts) {
    hardware->analogReads[7].push(1023);
    EXPECT_NEAR(5.0, sensor->readVoltage(), 0.01);
}

TEST_F(VoltageSensorTest, Reading2_5Volts) {
    hardware->analogReads[7].push(512);
    EXPECT_NEAR(2.5, sensor->readVoltage(), 0.01);
}

TEST_F(VoltageSensorTest, WithInterferenceAdjustment) {
    sensor->setInterferenceAdjustment(-0.6);
    hardware->analogReads[7].push(512);
    EXPECT_NEAR(1.9, sensor->readVoltage(), 0.01);
}
