#include <windows.h>
#include <stdio.h>
#include "backend.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    Game game = Game(SCREEN_WIDTH, SCREEN_HEIGHT);
    game.Init();
    game.Run();
    return 0;
}