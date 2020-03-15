#pragma once

#include <Arduino.h>
#include <map>
 
typedef std::map<const char *, char *> LogParameters;

enum LogLevel {
    LOG_LEVEL_OFF = 100,
    LOG_LEVEL_FATAL = 200,
    LOG_LEVEL_ERROR = 400,
    LOG_LEVEL_WARN = 500,
    LOG_LEVEL_INFO = 600,
    LOG_LEVEL_DEBUG = 700,
    LOG_LEVEL_TRACE = 800,
    LOG_LEVEL_ALL = 900,
};

class Logger
{
    char currentModule[20];
    uint32 lastTickMillis = 0;
    uint32 tickMultiplier = 1;
public:
    Logger();
    Logger(const char* module);

    void log(LogLevel level, const char* module, const char* message, LogParameters parameters);
    void fatal(const char* module, const char* message, LogParameters parameters);
    void fatal(const char* module, const char* message);
    void fatal(const char* message, LogParameters parameters);
    void fatal(const char* message);
    void error(const char* module, const char* message, LogParameters parameters);
    void error(const char* module, const char* message);
    void error(const char* message, LogParameters parameters);
    void error(const char* message);
    void warn (const char* module, const char* message, LogParameters parameters);
    void warn (const char* module, const char* message);
    void warn (const char* message, LogParameters parameters);
    void warn (const char* message);
    void info (const char* module, const char* message, LogParameters parameters);
    void info (const char* module, const char* message);
    void info (const char* message, LogParameters parameters);
    void info (const char* message);
    void debug(const char* module, const char* message, LogParameters parameters);
    void debug(const char* module, const char* message);
    void debug(const char* message, LogParameters parameters);
    void debug(const char* message);
    void trace(const char* module, const char* message, LogParameters parameters);
    void trace(const char* module, const char* message);
    void trace(const char* message, LogParameters parameters);
    void trace(const char* message);

    uint64 millisFromStart();
private:
    const char* levelStr(LogLevel level);
    const char* modulePath(const char* module);

    void printLog(LogLevel level, const char* module, const char* message, LogParameters parameters);
};
