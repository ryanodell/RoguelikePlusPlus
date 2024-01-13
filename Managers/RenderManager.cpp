#include "RenderManager.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
//int GameWidth;
//int GameHeight;
RenderManager& RenderManager::Get() {
    static RenderManager instance;
    return instance;
}

void RenderManager::IDraw(int x, int y, char character, unsigned char color) {

    m_renderUnits.push(RenderUnit(x, y, character, color));
}

void RenderManager::IRender() {
    int bufferWidth = 50;
    int bufferHeight = 20;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int totalUnits = m_renderUnits.size();
    //std::cout << "before: " << m_renderUnits.size() << std::endl;
    while(!m_renderUnits.empty()) {
        RenderUnit currentUnit = m_renderUnits.top();
        COORD coord;
        coord.X = currentUnit.X;
        coord.Y = currentUnit.Y;
        SetConsoleCursorPosition(hConsole, coord);
        SetConsoleTextAttribute(hConsole, currentUnit.Color);
        std::cout << currentUnit.Character;
        m_renderUnits.pop();
    }

}

void RenderManager::IClearScreen() {
    /*
    COORD topLeft  = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    FillConsoleOutputCharacterA(
        console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    FillConsoleOutputAttribute(
        console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        screen.dwSize.X * screen.dwSize.Y, topLeft, &written
    );
    SetConsoleCursorPosition(console, topLeft);
    */

    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

ConsoleRenderManager& ConsoleRenderManager::Get() {
    static ConsoleRenderManager instance;
    return instance;
}

void ConsoleRenderManager::IDraw(int x, int y, char character, unsigned char color) {

    m_renderUnits.push(RenderUnit(x, y, character, color));
}

void ConsoleRenderManager::IRender() {
    int bufferWidth = 50;
    int bufferHeight = 20;
    //Clear the buffer;
    memset(m_consoleBuffer, 0, sizeof(CHAR_INFO) * 50 * 20);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int totalUnits = m_renderUnits.size();
    //std::cout << "before: " << m_renderUnits.size() << std::endl;
    while(!m_renderUnits.empty()) {
        RenderUnit currentUnit = m_renderUnits.top();
        int index = currentUnit.Y * 50 + currentUnit.X;
        m_consoleBuffer[index].Char.AsciiChar = currentUnit.Character;
        m_consoleBuffer[index].Attributes = currentUnit.Color;
        SMALL_RECT writeRect = { 0, 0, bufferWidth - 1, bufferHeight - 1 };
        WriteConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), m_consoleBuffer, { bufferWidth, bufferHeight }, { 0, 0 }, &writeRect);
        m_renderUnits.pop();
    }
    //std::cout << "after: " << m_renderUnits.size() << std::endl;
    //Reset to white as default just in case
    SetConsoleTextAttribute(hConsole,
    FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
}

void ConsoleRenderManager::IClearScreen() {

}



