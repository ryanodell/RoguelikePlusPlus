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
    int GameWidth = 50;
    int GameHeight = 20;
    //RenderManager::Draw(test1X, test1Y, test1Char, test1Color);
    //RenderManager::Draw(8, 1, '<', FOREGROUND_GREEN|FOREGROUND_INTENSITY);

    for (int i = 0; i < GameHeight; i++)
    {
        for (int k = 0; k < GameWidth; k++)
        {
            // Left border
            if (k == 0)
                //std::cout << '|';
                RenderManager::Draw(k, i, '|', FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
            // player
            else if (i == test1X && k == test1Y)
                 RenderManager::Draw(test1X, test1Y, test1Char, test1Color);
                //std::cout << '@';
            // Right border
            else if (k + 1 == GameWidth)
                RenderManager::Draw(k, i, '|', FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
                //std::cout << '|';
            else
                //std::cout << ' ';
                RenderManager::Draw(k, i, ' ', FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED);
        }
        //std::cout << std::endl;
    }
    /*Color fun, keep for reference
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
    unsigned char greenish = FOREGROUND_GREEN;

    SetConsoleTextAttribute(hConsole,greenish);
    std::cout << "3";

    SetConsoleTextAttribute(hConsole,greenish|FOREGROUND_INTENSITY);
    std::cout << "4";
    SetConsoleTextAttribute(hConsole,
       FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
    firstFramePassed = true;
    */
}
