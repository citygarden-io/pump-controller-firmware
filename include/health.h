#pragma once

#include <Adafruit_INA219.h>
#include "log.h"

#ifndef INA219_WIRE_ADDRESS
#define INA219_WIRE_ADDRESS 0x40
#endif

class HealthService
{
    Adafruit_INA219 powerSensor;
    Logger log;

    float mainVoltage = 0.0f;    
    float mainCurrent = 0.0f;
    float mainPower = 0.0f;

    char* mainVoltageStr;
    char* mainCurrentStr;
    char* mainPowerStr;
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
};

extern HealthService Health;