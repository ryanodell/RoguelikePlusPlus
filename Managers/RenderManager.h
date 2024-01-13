#ifndef RENDERMANAGER_H_INCLUDED
#define RENDERMANAGER_H_INCLUDED
#include <stack>
#include <iostream>
#include <windows.h>

struct RenderUnit {
public:
    int X;
    int Y;
    char Character;
    unsigned char Color;
    RenderUnit();
    RenderUnit(int x, int y, char character, unsigned char color) {
        X = x;
        Y = y;
        Character = character;
        Color = color;
    }
};

class ConsoleRenderManager {
public:
    ConsoleRenderManager(const ConsoleRenderManager&) = delete;
    static ConsoleRenderManager& Get();
    static void Draw(int x, int y, char character, unsigned char color) {
        Get().IDraw(x, y, character, color);
    }
    static void Render() {
        Get().IRender();
    }
    static void ClearScreen() {
        Get().IClearScreen();
    }

private:
    ConsoleRenderManager() {
    }
    std::stack<RenderUnit> m_renderUnits;
    CHAR_INFO* m_consoleBuffer = new CHAR_INFO[50 * 20];
    void IDraw(int x, int y, char character, unsigned char color);
    void IRender();
    void IClearScreen();

private:
//eInputAction m_inputAction = NONE;
};

class RenderManager {
public:
    RenderManager(const RenderManager&) = delete;
    static RenderManager& Get();
    static void Draw(int x, int y, char character, unsigned char color) {
        Get().IDraw(x, y, character, color);
    }
    static void Render() {
        Get().IRender();
    }
    static void ClearScreen() {
        Get().IClearScreen();
    }

private:
    RenderManager() {}
    std::stack<RenderUnit> m_renderUnits;
    void IDraw(int x, int y, char character, unsigned char color);
    void IRender();
    void IClearScreen();
    //eInputAction IGetInput();

private:
//eInputAction m_inputAction = NONE;
};

#endif // RENDERMANAGER_H_INCLUDED
