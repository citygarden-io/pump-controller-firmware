#pragma once

#include <ESPAsyncWebServer.h>
#include "log.h"

#define HTTP_SERVICE_PORT 80

class HttpService
{
public:
    HttpService();
    void init();
    void loop();

private:
    AsyncWebServer *server;
    Logger log;

    void initHttpServer();

    void handleNotFound(AsyncWebServerRequest *request);
    void handleMetrics(AsyncWebServerRequest *request);

    void logRequest(AsyncWebServerRequest *request, uint16 statusCode);
};

extern HttpService HTTP;