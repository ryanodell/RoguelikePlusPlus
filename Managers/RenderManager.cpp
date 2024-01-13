#include "RenderManager.h"
#include <iostream>
#include <windows.h>

RenderManager& RenderManager::Get() {
    static RenderManager instance;
    return instance;
}

void RenderManager::IDraw(int x, int y, char character, unsigned char color) {

    m_renderUnits.push(RenderUnit(x, y, character, color));
    //m_renderUnits.push_back();
}

void RenderManager::IRender() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int totalUnits = m_renderUnits.size();
    //std::cout << totalUnits << std::endl;
    std::stack<RenderUnit> emptyStack;
    m_renderUnits.swap(emptyStack);
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
    //Reset to white as default just in case
    SetConsoleTextAttribute(hConsole,
    FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
}

void RenderManager::IClearScreen() {
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
