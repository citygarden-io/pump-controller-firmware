#include <Arduino.h>
#include <Log.h>

Logger::Logger()
{
    this->currentModule = NULL;
}

Logger::Logger(const char* module)
{
    this->currentModule = (char *) module;
}

void Logger::log(LogLevel level, const char* module, const char* message, LogParameters parameters)
{
    float secondFromStart = (float) this->millisFromStart() / 1000.0f;
    const char* levelStr = this->levelStr(level);
    const char* modulePath = this->modulePath(module);
    const char* parametersStr = this->parametersStr(parameters);
    
    Serial.printf_P(
        "[%12.4f] [%s] %s: %s [%s]\n",
        secondFromStart,
        modulePath,
        levelStr,
        message,
        parametersStr
    );
}

Logger Logger::module(const char* module)
{
    char* modulePath = (char *) this->modulePath(module);

    Serial.println(modulePath);

    return Logger(modulePath);
}

void Logger::info(const char* module, const char* message)
{
    this->log(LogLevel::LOG_LEVEL_INFO, module, message, LogParameters());
}

void Logger::info(const char* message, LogParameters parameters)
{
    this->log(LogLevel::LOG_LEVEL_INFO, NULL, message, parameters);
}

void Logger::info(const char* message)
{
    this->log(LogLevel::LOG_LEVEL_INFO, NULL, message, LogParameters());
}

void Logger::debug(const char* module, const char* message)
{
    this->log(LogLevel::LOG_LEVEL_DEBUG, module, message, LogParameters());
}


void Logger::debug(const char* message)
{
    this->log(LogLevel::LOG_LEVEL_DEBUG, NULL, message, LogParameters());
}

void Logger::trace(const char* module, const char* message)
{
    this->log(LogLevel::LOG_LEVEL_TRACE, module, message, LogParameters());
}

void Logger::trace(const char* message)
{
    this->log(LogLevel::LOG_LEVEL_TRACE, NULL, message, LogParameters());
}

const char* Logger::levelStr(LogLevel level)
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

const char* Logger::parametersStr(LogParameters parameters)
{
    if (parameters.size() == 0) {
        return "";
    }

    std::string buffer;
    LogParameters::iterator iterator = parameters.begin();
    
    while(iterator != parameters.end())
    {
        if (buffer.length() > 0) {
            buffer.append(", ");
        }

        buffer.append(iterator->first);
        buffer.append(": '");
        buffer.append(iterator->second);
        buffer.append("'");

        iterator++;
    }

    return buffer.c_str();
}

uint64 Logger::millisFromStart()
{
    uint32 currentMillis = millis();

    if (currentMillis < this->lastTickMillis) {
        this->tickMultiplier++;
    }

    this->lastTickMillis = currentMillis;

    return currentMillis * this->tickMultiplier;
}

const char* Logger::modulePath(const char* module)
{
    bool currentModuleSetted = (this->currentModule != NULL && strlen(this->currentModule) > 0);
    bool newModuleSetted = (module != NULL && strlen(module) > 0);

    if (currentModuleSetted && !newModuleSetted) {
        return this->currentModule;
    }

    if (!currentModuleSetted && newModuleSetted) {
        return module;
    }

    if (currentModuleSetted && newModuleSetted) {
        String modulePath = String(this->currentModule) + String(".") + String(module);
        return modulePath.c_str();
    }

    return "";
}

Logger Log("MAIN");