#include <ESPAsyncWebServer.h>
#include "http.h"

HttpService::HttpService()
{
    this->log = Logger("HttpService");
    this->server = new AsyncWebServer(HTTP_SERVICE_PORT);
}

void HttpService::init()
{
    this->initHttpServer();
}

void HttpService::loop()
{
}

void HttpService::initHttpServer()
{
    this->log.info("Initializing HTTP server.");
    this->server->begin();

    this->server->onNotFound(std::bind(&HttpService::handleNotFound, this, std::placeholders::_1));
    this->server->on("/metrics", HTTP_GET, std::bind(&HttpService::handleMetrics, this, std::placeholders::_1));

    this->log.info("HTTP server is initialized.");
}

void HttpService::handleMetrics(AsyncWebServerRequest *request)
{
    this->logRequest(request, 200);

    AsyncResponseStream *response = request->beginResponseStream("text/plain");
    response->write("# This is prometheus endpoint.\n");

    request->send(response);
}

void HttpService::handleNotFound(AsyncWebServerRequest *request)
{
    this->logRequest(request, 404);

    request->send(404, "application/json", "{\"error\": {\"code\": 404, \"message\": \"Endpoint not found.\"}}");
}

void HttpService::logRequest(AsyncWebServerRequest *request, uint16 statusCode)
{
    char urlStr[256] = {0};
    char statusCodeStr[4] = {0};

    strcat(urlStr, (const char *)request->url().c_str());
    sprintf(statusCodeStr, "%d", statusCode);

    LogParameters requestParameters = LogParameters{
        {"url", urlStr},
        {"statusCode", statusCodeStr},
    };

    if (statusCode >= 200 && statusCode <= 210)
    {
        this->log.info("HTTP request.", requestParameters);
    }
    else
    {
        this->log.warn("HTTP request.", requestParameters);
    }
}

HttpService HTTP = HttpService();