#ifndef LOGGER_H
#define LOGGER_H
#include <stdio.h>
#include <stdarg.h>
#include <windows.h>
namespace Logger {
    void LogFormatted(const char* format, ...);
    void LogInfo(const char* format);
    void LogWarning(const char* format);
    void LogError(const char* format);
}


#endif // LOGGER_H
