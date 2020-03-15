#pragma once

#include <ESP8266WiFi.h>
#include "log.h"

#define NETWORK_LOG_INTERVAL 5000

class NetworkManager
{
public:
    NetworkManager();

    void init();
    void loop();

    wl_status_t getWIFIStatus();
    const char* wifiStatusStr(wl_status_t wifiStatus);
private:
    wl_status_t wifiStatus = WL_IDLE_STATUS;
    Logger log;
    uint64 lastLogMillis = 0;

    void loopWIFI();
    void loopLog();
    void initWIFI();
};

extern NetworkManager Network;
