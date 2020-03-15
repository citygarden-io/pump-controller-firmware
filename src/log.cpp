#include <Arduino.h>
#include "log.h"

Logger::Logger()
{
    strcpy(this->currentModule, "Unknown");
}

Logger::Logger(const char *module)
{
    strcpy(this->currentModule, module);
}

void Logger::log(LogLevel level, const char *module, const char *message, LogParameters parameters)
{
    this->printLog(level, module, message, parameters);
}

void Logger::info(const char *module, const char *message)
{
    this->log(LogLevel::LOG_LEVEL_INFO, module, message, LogParameters());
}

void Logger::info(const char *message, LogParameters parameters)
{
    this->log(LogLevel::LOG_LEVEL_INFO, NULL, message, parameters);
}

void Logger::info(const char *message)
{
    this->log(LogLevel::LOG_LEVEL_INFO, NULL, message, LogParameters());
}

void Logger::warn(const char *message)
{
    this->log(LogLevel::LOG_LEVEL_WARN, NULL, message, LogParameters());
}

void Logger::warn(const char *message, LogParameters parameters)
{
    this->log(LogLevel::LOG_LEVEL_WARN, NULL, message, parameters);
}

void Logger::debug(const char *module, const char *message)
{
    this->log(LogLevel::LOG_LEVEL_DEBUG, module, message, LogParameters());
}

void Logger::debug(const char *module, const char *message, LogParameters parameters)
{
    this->log(LogLevel::LOG_LEVEL_DEBUG, module, message, parameters);
}

void Logger::debug(const char *message)
{
    this->log(LogLevel::LOG_LEVEL_DEBUG, NULL, message, LogParameters());
}

void Logger::trace(const char *module, const char *message, LogParameters parameters)
{
    this->log(LogLevel::LOG_LEVEL_TRACE, module, message, parameters);
}

void Logger::trace(const char *message, LogParameters parameters)
{
    this->log(LogLevel::LOG_LEVEL_TRACE, NULL, message, parameters);
}

void Logger::trace(const char *module, const char *message)
{
    this->log(LogLevel::LOG_LEVEL_TRACE, module, message, LogParameters());
}

void Logger::trace(const char *message)
{
    this->log(LogLevel::LOG_LEVEL_TRACE, NULL, message, LogParameters());
}

const char *Logger::levelStr(LogLevel level)
{
    switch (level)
    {
    case LogLevel::LOG_LEVEL_FATAL:
        return "FATAL";
        break;
    case LogLevel::LOG_LEVEL_ERROR:
        return "ERROR";
        break;
    case LogLevel::LOG_LEVEL_WARN:
        return "WARN";
        break;
    case LogLevel::LOG_LEVEL_INFO:
        return "INFO";
        break;
    case LogLevel::LOG_LEVEL_DEBUG:
        return "DEBUG";
        break;
    case LogLevel::LOG_LEVEL_TRACE:
        return "TRACE";
        break;
    default:
        return "UNKNOWN";
        break;
    }
}

void Logger::printLog(LogLevel level, const char *module, const char *message, LogParameters parameters)
{
    float secondFromStart = (float)this->millisFromStart() / 1000.0f;
    const char *levelStr = this->levelStr(level);
    const char *modulePath = this->modulePath(module);

    Serial.printf_P(
        "[%12.4f] [%s] %s: %s ",
        secondFromStart,
        modulePath,
        levelStr,
        message);

    LogParameters::iterator iterator = parameters.begin();
    while (iterator != parameters.end())
    {
        Serial.printf_P(
            "[%s: %s] ",
            iterator->first,
            iterator->second);

        iterator++;
    }

    Serial.print("\n");
}

uint64 Logger::millisFromStart()
{
    uint32 currentMillis = millis();

    if (currentMillis < this->lastTickMillis)
    {
        this->tickMultiplier++;
    }

    this->lastTickMillis = currentMillis;

    return currentMillis * this->tickMultiplier;
}

const char *Logger::modulePath(const char *module)
{
    bool currentModuleSetted = (this->currentModule != NULL && strlen(this->currentModule) > 0);
    bool newModuleSetted = (module != NULL && strlen(module) > 0);

    if (currentModuleSetted && !newModuleSetted)
    {
        return this->currentModule;
    }

    if (!currentModuleSetted && newModuleSetted)
    {
        return module;
    }

    if (currentModuleSetted && newModuleSetted)
    {
        std::string buffer;
        buffer.append(this->currentModule);
        buffer.append(".");
        buffer.append(module);
        return buffer.c_str();
    }

    return "";
}
