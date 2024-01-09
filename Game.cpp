#include "Game.h"
#include <iostream>

eInputAction inputAction;


void Game::handleInput() {
    char key = 0;
    while (!_kbhit()) {
        //pause execution
    }
    key = _getch();
    switch (key) {
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
}

Game::Game(int width, int height) {
    Width = width;
    Height = height;
    PlayerX = 3;
    PlayerY = 3;
    isRunning = true;
    //screenManager = ScreenManager::GetInstance();
}

bool Game::IsRunning() {
    return isRunning;
}

void Game::OnLoad() {
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(consoleHandle, &consoleInfo);
    consoleInfo.bVisible = false;
}

void Game::Update(int frame) {
    handleInput();
    ScreenManager::GetInstance().Update();
    if(inputAction == RIGHT) {
        PlayerX++;
    }
    if(inputAction == LEFT) {
        PlayerX--;
    }
    if(inputAction == DOWN) {
        PlayerY++;
    }
    if(inputAction == UP) {
        PlayerY--;
    };
}


void Game::EndFrame() {
    SetConsoleCursorInfo(consoleHandle, &consoleInfo);
}


void Game::Draw(int frame) {
    clearScreen();
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
            // player
            else if (i == PlayerY && k == PlayerX)
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
    std::cout << "Current Frame: " << frame << std::endl;
    std::cout << "X: " << PlayerX << std::endl;
    std::cout << "Y: " << PlayerY << std::endl;
}

void Game::clearScreen() {
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

Game::~Game() {

}
