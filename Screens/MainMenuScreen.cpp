#include "../ScreenManager.h"
#include "MainMenuScreen.h"
#include "OverworldScreen.h"
#include "../Managers/InputManager.h"
#include <iostream>

bool firstFramePassed = false;


static int test1X = 3;
static int test1Y = 4;
static unsigned char test1Color = FOREGROUND_BLUE;
static char test1Char = '@';


void MainMenuScreen::OnLoad() const {

}

void MainMenuScreen::Update(int frame) const {
    eInputAction inputAction = InputManager::GetInput();
    if(inputAction == NONE) {
        ScreenManager::GetInstance().ChangeScreen("overworld");
    }
    if(inputAction == RIGHT) {
        test1X++;
    }
    /*
    if(firstFramePassed == true) {
        InputManager::GetInput();
        ScreenManager::GetInstance().ChangeScreen("overworld");
    }
    firstFramePassed = true;
    */
}

void MainMenuScreen::Draw(int frame) const {
    ConsoleRenderManager::Draw(test1X, test1Y, test1Char, test1Color);
    ConsoleRenderManager::Draw(8, 1, '<', FOREGROUND_GREEN|FOREGROUND_INTENSITY);
}
