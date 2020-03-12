#include <Arduino.h>
#include <ESP8266WiFi.h>

// #include "log.h"
#include "network.h"

#ifndef WIFI_SSID
#define WIFI_SSID "citygarden.io IoT"
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "Xspa5rur!mehe@ov"
#endif

NetworkManager::NetworkManager()
{
    this->log = Logger("NetworkManager");
}

void NetworkManager::init()
{
    this->log.info("Initializing.");

    WiFi.setAutoReconnect(true);
    WiFi.persistent(false);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    this->log.debug("WiFi parameters setted.");

    this->log.info("Initialized.");
}

void NetworkManager::loop()
{
    this->loopWIFI();
}

wl_status_t NetworkManager::getWIFIStatus()
{
    return this->wifiStatus;
}

const char* NetworkManager::wifiStatusStr(wl_status_t wifiStatus)
{
    switch (wifiStatus) {
        case WL_NO_SHIELD:
            return "NO_SHIELD";
            break;
        case WL_IDLE_STATUS:
            return "IDLE";
            break;
        case WL_NO_SSID_AVAIL:
            return "NO_SSID_AVAILABLE";
            break;
        case WL_SCAN_COMPLETED:
            return "SCAN_COMPLETED";
            break;
        case WL_CONNECTED:
            return "CONNECTED";
            break;
        case WL_CONNECT_FAILED:
            return "CONNECT_FAILED";
            break;
        case WL_CONNECTION_LOST:
            return "CONNECTION_LOST";
            break;
        case WL_DISCONNECTED:
            return "DISCONNECTED";
            break;
    }

    return "UNKNOWN";
}

void NetworkManager::loopWIFI()
{
    wl_status_t currentWIFIStatus = WiFi.status();
    wl_status_t previousWIFIStatus = this->wifiStatus;

    if (previousWIFIStatus != currentWIFIStatus) {
        this->wifiStatus = currentWIFIStatus;
        LogParameters parameters = LogParameters{
            { "previousStatus", (char *) this->wifiStatusStr(previousWIFIStatus) },
            { "currentStatus",  (char *) this->wifiStatusStr(currentWIFIStatus) },
        };
        this->log.info("WiFi status changed.", parameters);
    }
}

NetworkManager Network = NetworkManager();