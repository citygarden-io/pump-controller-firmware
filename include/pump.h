#pragma once

#include "log.h"

#ifndef PUMP_CONTROLLER_WIRE_ADDRESS
#define PUMP_CONTROLLER_WIRE_ADDRESS 0x15
#endif

#define PUMP_CONTROLLER_READ_INTERVAL 900
#define PUMP_CONTROLLER_WRITE_INTERVAL 900

#define PUMP_CONTROLLER_REGISTER_STATUS 0x01
#define PUMP_CONTROLLER_REGISTER_PUMP_N_DESIRED_FLOW 0x10 // Internal use
#define PUMP_CONTROLLER_REGISTER_PUMP_1_DESIRED_FLOW 0x11
#define PUMP_CONTROLLER_REGISTER_PUMP_2_DESIRED_FLOW 0x12
#define PUMP_CONTROLLER_REGISTER_PUMP_3_DESIRED_FLOW 0x13
#define PUMP_CONTROLLER_REGISTER_PUMP_4_DESIRED_FLOW 0x14
#define PUMP_CONTROLLER_REGISTER_PUMP_5_DESIRED_FLOW 0x15
#define PUMP_CONTROLLER_REGISTER_PUMP_6_DESIRED_FLOW 0x16
#define PUMP_CONTROLLER_REGISTER_PUMP_N_CURRENT_FLOW 0x20 // Internal use
#define PUMP_CONTROLLER_REGISTER_PUMP_1_CURRENT_FLOW 0x21
#define PUMP_CONTROLLER_REGISTER_PUMP_2_CURRENT_FLOW 0x22
#define PUMP_CONTROLLER_REGISTER_PUMP_3_CURRENT_FLOW 0x23
#define PUMP_CONTROLLER_REGISTER_PUMP_4_CURRENT_FLOW 0x24
#define PUMP_CONTROLLER_REGISTER_PUMP_5_CURRENT_FLOW 0x25
#define PUMP_CONTROLLER_REGISTER_PUMP_6_CURRENT_FLOW 0x26

class PumpController
{
public:
    PumpController();

    void init();
    void loop();    
private:
    Logger log;
    bool pumpControllerInitialized = false;
    uint64 lastReadMilis = 0;
    uint64 lastWriteMilis = 0;

    char desiredFlowRate[6] = {0};
    char currentFlowRate[6] = {0};

    void loopReadCurrentFlowRate();
    void loopWriteDesiredFlowRate();
    void initPumpController();

    char wireReadRegister(char registerNumber);
    void wireWriteRegister(char registerNumber, char value);
};

extern PumpController Pump;