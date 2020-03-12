#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include "health.h"
#include "log.h"

HealthService::HealthService()
{
    this->log = Logger("HealthService");
    this->powerSensor = Adafruit_INA219(INA219_WIRE_ADDRESS);

    this->mainVoltageStr = new char[8];
    this->mainCurrentStr = new char[8];
    this->mainPowerStr = new char[8];
}

void HealthService::init() 
{
    this->initPowerSensor();
}

void HealthService::loop()
{
    this->loopPowerSensor();
    this->loopHealthLog();
    this->loopHealthMetric();
}

void HealthService::initPowerSensor()
{
    this->log.info("Initializing INA219 module.");
    this->powerSensor.begin();
    this->log.info("INA219 module is initialized.");
}

void HealthService::loopPowerSensor()
{
    this->mainVoltage = this->powerSensor.getBusVoltage_V();
    this->mainCurrent = this->powerSensor.getCurrent_mA() / 1000;
    this->mainPower   = this->powerSensor.getPower_mW() / 1000;

    sprintf(this->mainVoltageStr, "%6.4f", this->mainVoltage);
    sprintf(this->mainCurrentStr, "%6.4f", this->mainCurrent);
    sprintf(this->mainPowerStr, "%6.4f", this->mainPower);
}

float HealthService::getMainVoltage()
{
    return this->mainVoltage;
}

float HealthService::getMainCurrent()
{
    return this->mainCurrent;
}

float HealthService::getMainPower()
{
    return this->mainPower;
}

char* HealthService::getMainVoltageStr()
{
    return this->mainVoltageStr;
}

char* HealthService::getMainCurrentStr()
{
    return this->mainCurrentStr;
}

char* HealthService::getMainPowerStr()
{
    return this->mainPowerStr;
}

void HealthService::loopHealthLog()
{
    LogParameters parameters = LogParameters{
        { "mainVoltage", this->mainVoltageStr },
        { "mainCurrent",  this->mainCurrentStr },
        { "mainPower",  this->mainPowerStr },
    };
    this->log.info("Current health.", parameters);
}

void HealthService::loopHealthMetric()
{
    
}

HealthService Health = HealthService();
