#include "Logger.h"

namespace Logger {
    void LogFormatted(const char *format, ...) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
        va_list args;
        va_start(args, format);
        printf("\033[1;33m[WARNING] "); 
        vprintf(format, args);
        va_end(args);
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); // Reset to default
    }
}
