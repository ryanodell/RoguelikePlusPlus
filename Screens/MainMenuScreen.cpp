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
    std::cout << "Press any key to play:" << std::endl;
    firstFramePassed = true;
}
