#include "../ScreenManager.h"
#include "MainMenuScreen.h"
#include "OverworldScreen.h"
#include <iostream>

bool firstFramePassed = false;
void MainMenuScreen::OnLoad() const {

}

void MainMenuScreen::Update(int frame) const {
    if(firstFramePassed == true) {
        while (!_kbhit()) {
            //pause execution
        }
        //_getch();
        ScreenManager::GetInstance().ChangeScreen("overworld");
    }
}

void MainMenuScreen::Draw(int frame) const {
    std::cout << "Press any key to play:" << std::endl;
    firstFramePassed = true;
}
