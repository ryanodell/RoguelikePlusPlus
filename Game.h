#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <iostream>
#include <windows.h>
#include <conio.h>

class Game {
public:
    Game(int width, int height);
    ~Game();
    void OnLoad();
    void Update(int frame);
    void Draw(int frame);
    int PlayerX, PlayerY;
private:
    int Width;
    int Height;
    void clearScreen();
    void handleInput();
};

#endif // GAME_H_INCLUDED
