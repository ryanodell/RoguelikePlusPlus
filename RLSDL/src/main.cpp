#include <windows.h>
#include "backend.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    printf("..STARTING..");
    Game game = Game(SCREEN_WIDTH, SCREEN_HEIGHT, "RLSDL");
    if(!game.Init()) {
        printf("There was an error during initialization process. Check Logs");
        return -1;
    }
    game.Run();
    return 0;
}