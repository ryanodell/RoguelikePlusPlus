#include <iostream>
#include <windows.h>

void drawToBuffer(CHAR_INFO* buffer, int x, int y, char character, unsigned char color) {

     int index = y * 50 + x;
    //buffer[y * 80 + x].Char.AsciiChar = character;
    //buffer[y * 80 + x].Attributes = color;
    buffer[index].Char.AsciiChar = character;
    buffer[index].Attributes = color;
}

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    int bufferWidth = 50;//csbi.dwSize.X;
    int bufferHeight = 20;//csbi.dwSize.Y;

    CHAR_INFO* buffer = new CHAR_INFO[bufferWidth * bufferHeight];
    int x = 0;
    while(true) {
        //Clear
        memset(buffer, 0, sizeof(CHAR_INFO) * bufferWidth * bufferHeight);
        // Draw to the buffer
        drawToBuffer(buffer, x, 5, 'X', FOREGROUND_GREEN);
        drawToBuffer(buffer, x+1, 1, 'P', FOREGROUND_RED);
        drawToBuffer(buffer, x+7, 7, '@', FOREGROUND_BLUE|FOREGROUND_INTENSITY);
        //drawToBuffer(buffer, 6, 1, 'Y', FOREGROUND_RED);

        // Write the entire buffer to the console
        SMALL_RECT writeRect = { 0, 0, bufferWidth - 1, bufferHeight - 1 };
        WriteConsoleOutput(hConsole, buffer, { bufferWidth, bufferHeight }, { 0, 0 }, &writeRect);
        Sleep(5);
        x++;
    }
    // Display some other text to see the modification

    delete[] buffer;

    return 0;
}
