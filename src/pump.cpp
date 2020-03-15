#include <Wire.h>
#include "pump.h"

PumpController::PumpController()
{
    this->log = Logger("PumpController");
}

void PumpController::init()
{
    this->log.info("Initializing.");

    this->initPumpController();

    this->log.info("Initializing.");
}

void PumpController::loop()
{
    if (!this->pumpControllerInitialized) {
        return;
    }

    this->loopReadCurrentFlowRate();
    this->loopWriteDesiredFlowRate();
}

void PumpController::loopWriteDesiredFlowRate()
{
    if (this->log.millisFromStart() - this->lastWriteMillis < PUMP_CONTROLLER_WRITE_INTERVAL) {
        return;
    }

    this->wireWriteRegister(PUMP_CONTROLLER_REGISTER_PUMP_1_DESIRED_FLOW, this->desiredFlowRate[0]);
    delay(10);
    this->wireWriteRegister(PUMP_CONTROLLER_REGISTER_PUMP_2_DESIRED_FLOW, this->desiredFlowRate[1]);
    delay(10);
    this->wireWriteRegister(PUMP_CONTROLLER_REGISTER_PUMP_3_DESIRED_FLOW, this->desiredFlowRate[2]);
    delay(10);
    this->wireWriteRegister(PUMP_CONTROLLER_REGISTER_PUMP_4_DESIRED_FLOW, this->desiredFlowRate[3]);
    delay(10);
    this->wireWriteRegister(PUMP_CONTROLLER_REGISTER_PUMP_5_DESIRED_FLOW, this->desiredFlowRate[4]);
    delay(10);
    this->wireWriteRegister(PUMP_CONTROLLER_REGISTER_PUMP_6_DESIRED_FLOW, this->desiredFlowRate[5]);
    delay(10);

    this->lastWriteMillis = log.millisFromStart();
}

void PumpController::loopReadCurrentFlowRate()
{
    if (this->log.millisFromStart() - this->lastReadMillis < PUMP_CONTROLLER_READ_INTERVAL) {
        return;
    }

    this->currentFlowRate[0] = this->wireReadRegister(PUMP_CONTROLLER_REGISTER_PUMP_1_CURRENT_FLOW);
    delay(10);
    this->currentFlowRate[1] = this->wireReadRegister(PUMP_CONTROLLER_REGISTER_PUMP_2_CURRENT_FLOW);
    delay(10);
    this->currentFlowRate[2] = this->wireReadRegister(PUMP_CONTROLLER_REGISTER_PUMP_3_CURRENT_FLOW);
    delay(10);
    this->currentFlowRate[3] = this->wireReadRegister(PUMP_CONTROLLER_REGISTER_PUMP_4_CURRENT_FLOW);
    delay(10);
    this->currentFlowRate[4] = this->wireReadRegister(PUMP_CONTROLLER_REGISTER_PUMP_5_CURRENT_FLOW);
    delay(10);
    this->currentFlowRate[5] = this->wireReadRegister(PUMP_CONTROLLER_REGISTER_PUMP_6_CURRENT_FLOW);
    delay(10);

    this->lastReadMillis = log.millisFromStart();
}

void PumpController::initPumpController()
{
    this->log.info("Initializing i2c-pump-controller.");

    char status = this->wireReadRegister(PUMP_CONTROLLER_REGISTER_STATUS);

    if (status != 0xFF) {
        this->log.info("I2C-pump-controller was NOT initialized.", LogParameters{
            { "reply", &status }
        });
        return;
    }

    this->pumpControllerInitialized = true;

    this->log.info("I2C-pump-controller is initialized.");
}

char PumpController::wireReadRegister(char registerNumber)
{
    char value;

    Wire.beginTransmission(PUMP_CONTROLLER_WIRE_ADDRESS);
    Wire.write(registerNumber);
    Wire.endTransmission(false);

    Wire.requestFrom(PUMP_CONTROLLER_WIRE_ADDRESS, 1);
    Wire.readBytes(&value, 1);

    while (Wire.available()) {
        Wire.read();
    }

    return value;
}

void PumpController::wireWriteRegister(char registerNumber, char value)
{
    Wire.beginTransmission(PUMP_CONTROLLER_WIRE_ADDRESS);
    Wire.write(registerNumber);
    Wire.write(value);
    Wire.endTransmission(true);
}

PumpController Pump = PumpController();