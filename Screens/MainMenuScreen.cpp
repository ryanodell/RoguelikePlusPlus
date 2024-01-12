#include "../ScreenManager.h"
#include "MainMenuScreen.h"
#include "OverworldScreen.h"
#include "../Managers/InputManager.h"
#include <iostream>

bool firstFramePassed = false;
void MainMenuScreen::OnLoad() const {

}

void MainMenuScreen::Update(int frame) const {
    if(firstFramePassed == true) {
        InputManager::GetInput();
        ScreenManager::GetInstance().ChangeScreen("overworld");
    }
}

void MainMenuScreen::Draw(int frame) const {
    unsigned char color = 201;
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(hConsole, color);
    //White
    SetConsoleTextAttribute(hConsole,
       FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    std::cout << "Press any key to play:" << std::endl;
    //Red
    SetConsoleTextAttribute(hConsole,
       FOREGROUND_RED|FOREGROUND_INTENSITY);
    std::cout << "1";
        //Blue
    SetConsoleTextAttribute(hConsole,
       FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    std::cout << "2";

    //Green-ish
    unsigned char greenish = FOREGROUND_GREEN|FOREGROUND_INTENSITY;
    SetConsoleTextAttribute(hConsole,greenish);
    std::cout << "3";
    SetConsoleTextAttribute(hConsole,
       FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    firstFramePassed = true;
}
