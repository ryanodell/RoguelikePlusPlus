#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>
#include <stdarg.h>
#include <windows.h>


namespace Logger {
    
    enum class LogLevel : unsigned int {
        Info = 0x00,
        Warning = 0x01,
        Error = 0x02,
        None = 0x03
    };
    void LogInfo(const char* format, ...);
    void LogWarning(const char* format, ...);
    void LogError(const char* format, ...);

    void Log(LogLevel level, const char* format, ...);
}


#endif // LOGGER_H
