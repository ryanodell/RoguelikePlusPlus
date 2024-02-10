#include "Logger.h"

namespace Logger {
    static HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    static void reset(va_list args) {
        va_end(args);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to default
        printf("\n");
    }
    void LogInfo(const char *format, ...) {
        va_list args;
        va_start(args, format);
        printf("[INFO] ");
        vprintf(format, args);
        reset(args);
    }
    void LogWarning(const char *format, ... ){
        va_list args;
        va_start(args, format);
        SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
        printf("[WARNING] ");
        vprintf(format, args);
        reset(args);
    }
    void LogError(const char *format, ...) {
        va_list args;
        va_start(args, format);
        SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED);
        printf("[ERROR] ");
        vprintf(format, args);
        reset(args);
    }
    void Log(LogLevel level, const char *format, ...)
    {
        //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        va_list args;
        va_start(args, format);
        switch (level) {
        case LogLevel::Info:
            printf("[INFO] ");
            break;
        case LogLevel::Warning:
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
            printf("[WARNING] ");
            break;
        case LogLevel::Error:
            SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED);
            printf("[ERROR] ");
            break;
        default:
            break;
        }
        vprintf(format, args);
        va_end(args);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to default
        printf("\n");
    }
}
