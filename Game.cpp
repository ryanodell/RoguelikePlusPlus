#include "Game.h"
#include <iostream>
#include "Screens/ScreenBase.h"
#include "Screens/OverworldScreen.h"
#include "Globals.h"
#include "Managers/RenderManager.h"

eInputAction inputAction;
/*
MainMenuScreen mainMenuScreen;
OverworldScreen overworldScreen;
*/

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

Game::Game(int width, int height) : Width(width), Height(height) {
    PlayerX = 3;
    PlayerY = 3;
    isRunning = true;
}

bool Game::IsRunning() {
    return isRunning;
}

void Game::OnLoad() {
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(consoleHandle, &consoleInfo);
    consoleInfo.bVisible = false;
    ScreenManager::GetInstance().ChangeScreen("mainMenu");
}

void Game::Update(int frame) {
    //handleInput();
    ScreenManager::GetInstance().Update(frame);
    /*
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
    */
}


void Game::EndFrame() {
    SetConsoleCursorInfo(consoleHandle, &consoleInfo);
}


void Game::Draw(int frame) {
    ScreenManager::GetInstance().Draw(frame);
}
Game::~Game() {

}
