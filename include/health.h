#pragma once

#include <Adafruit_INA219.h>
#include "log.h"

#ifndef INA219_WIRE_ADDRESS
#define INA219_WIRE_ADDRESS 0x40
#endif

#define HEALTH_LOG_INTERVAL 1000
#define HEALTH_POWER_READ_INTERVAL 100

class HealthService
{
public:
    HealthService();

    void init();
    void loop();

    float getMainVoltage();
    float getMainCurrent();
    float getMainPower();

    char* getMainVoltageStr();
    char* getMainCurrentStr();
    char* getMainPowerStr();
private:
    void initPowerSensor();
    void loopPowerSensor();
    void loopHealthLog();
    void loopHealthMetric();

    Adafruit_INA219 powerSensor;
    Logger log;

    uint64 lastLogMillis = 0;
    uint64 lastPowerReadMillis = 0;

    float mainVoltage = 0.0f;    
    float mainCurrent = 0.0f;
    float mainPower = 0.0f;

    char* mainVoltageStr;
    char* mainCurrentStr;
    char* mainPowerStr;
};

extern HealthService Health;
