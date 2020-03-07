#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <map>
#include "Log.h"
#include "network.h"

#ifndef WIFI_SSID
#define WIFI_SSID "citygarden.io IoT"
#endif

#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "Xspa5rur!mehe@ov"
#endif

NetworkManager::NetworkManager()
{
    this->logger = Log.module("NETWORK");
}

void NetworkManager::init()
{
    this->logger.info("Initializing.");

    WiFi.setAutoReconnect(true);
    WiFi.persistent(false);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    this->logger.debug("WiFi parameters setted.");

    this->logger.info("Initialized.");
}

void NetworkManager::loop()
{
    wl_status_t currentWIFIStatus = WiFi.status();
    wl_status_t previousWIFIStatus = this->wifiStatus;

    if (previousWIFIStatus != currentWIFIStatus) {
        this->wifiStatus = currentWIFIStatus;
        LogParameters parameters = LogParameters{
            { "previousStatus", this->wifiStatusStr(previousWIFIStatus) },
            { "currentStatus",  this->wifiStatusStr(currentWIFIStatus) },
        };
        this->logger.info("WiFi status changed.", parameters);
    }
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

NetworkManager Network;