#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "log.h"

class NetworkManager
{
    wl_status_t wifiStatus = WL_IDLE_STATUS;
    Logger logger;
public:
    NetworkManager();
    void init();
    void loop();
    wl_status_t getWIFIStatus();
    const char* wifiStatusStr(wl_status_t wifiStatus);
};

extern NetworkManager Network;