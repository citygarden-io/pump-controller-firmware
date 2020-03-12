#pragma once

#include <ESP8266WiFi.h>
#include "log.h"


class NetworkManager
{
    wl_status_t wifiStatus = WL_IDLE_STATUS;
    Logger log;
public:
    NetworkManager();

    void init();
    void loop();
    wl_status_t getWIFIStatus();
    const char* wifiStatusStr(wl_status_t wifiStatus);
private:
    void loopWIFI();
};

extern NetworkManager Network;
