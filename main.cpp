#include "Game.h"
bool isRunning = true;
int currentFrame = 1;

int main() {
    Game game(50, 20);
    game.OnLoad();
    while(isRunning) {
        game.Update(currentFrame);
        game.Draw(currentFrame);
        currentFrame++;
        HANDLE consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO consoleInfo;
        GetConsoleCursorInfo(consoleOut, &consoleInfo);
        consoleInfo.bVisible = false;
        SetConsoleCursorInfo(consoleOut, &consoleInfo);
    }

    return 0;
}

/*
#include <iostream>
#include <windows.h>
#include <conio.h>

//Global vars
bool isRunning = true;
const int Width = 30;
const int Height = 20;
int currentFrame = 1;
int frameTimer = 1000;
int X, Y;

enum eInputAction {
    NONE, UP, DOWN, LEFT, RIGHT
};

eInputAction inputAction;

void ClearScreen() {
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void HandleInput() {
    char key = 0;
    while (!_kbhit()) {
        //pause execution
    }
    key = _getch();
    //if (_kbhit())
    //{
        switch (key)
        {
        case 'w':
            inputAction = UP;
            break;
        case 'a':
            inputAction = LEFT;
            break;
        case 's':
            inputAction = DOWN;
            break;
        case 'd':
            inputAction = RIGHT;
            break;
        case 'k':
            isRunning = false;
            break;
        }
    //}
}

void Init() {
    X = 0;
    Y = 0;
}

void Draw() {
    ClearScreen();
    //top border
    for (int i = 0; i < Width + 2; i++) {
        std::cout << '-';
    }
    std::cout << std::endl;

    for (int i = 0; i < Height; i++)
    {
        for (int k = 0; k < Width; k++)
        {
            // Left border
            if (k == 0)
                std::cout << '|';
            // Snake's head
            else if (i == Y && k == X)
                std::cout << '@';
            // Right border
            else if (k + 1 == Width)
                std::cout << '|';
            else
                std::cout << ' ';
        }
        std::cout << std::endl;
    }

        // Draws bottom border
    for (int i = 0; i < Width + 2; i++)
        std::cout << '-';
    std::cout << std::endl;

    //Display current frame:
    std::cout << std::endl;
    std::cout << "Current Frame: " << currentFrame << std::endl;
    std::cout << "X: " << X << std::endl;
}

void Update() {
    HandleInput();
    if(inputAction == RIGHT) {
        X++;
    }
    if(inputAction == LEFT) {
        X--;
    }
    if(inputAction == DOWN) {
        Y++;
    }
    if(inputAction == UP) {
        Y--;
    };
}

int main() {
    Init();
    while(isRunning) {
        Update();
        Draw();
        inputAction = NONE;
        currentFrame++;
        HANDLE consoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO consoleInfo;
        GetConsoleCursorInfo(consoleOut, &consoleInfo);
        consoleInfo.bVisible = false;
        SetConsoleCursorInfo(consoleOut, &consoleInfo);
        //Sleep(frameTimer);
    }
    return 0;
}
*/
