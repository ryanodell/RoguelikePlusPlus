#include <windows.h>
#include "backend.h"
#include <cassert>
#include "core/macros.h"
#include "components.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
Logger::LogLevel MIN_LOG_LEVEL = Logger::LogLevel::Info;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    
    Renderable rend;
    rend.Position = Vec2();
    rend.Texture = nullptr;
    

    Logger::LogInfo("..STARTING..");
    Game game = Game(SCREEN_WIDTH, SCREEN_HEIGHT, "RLSDL");
    if(!game.Init()) {
        Logger::LogError("There was an error during initialization process. Check Logs");
        return -1;
    }
    game.Run();
    //getchar();
    return 0;
}