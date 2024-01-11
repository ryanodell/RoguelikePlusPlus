#include "Game.h"
#include "Globals.h"

bool isRunning = true;
int currentFrame = 1;
int GameWidth = 50;
int GameHeight = 20;

int main() {
    /*
    const char* name = "test";
    if(name == "test") {
        std::cout << "Matches" << std::endl;
    }
    else {
        std::cout << "Doens't match" << std::endl;
    }
    */

    Game game(GameWidth, GameHeight);
    game.OnLoad();
    while(game.IsRunning()) {
        game.Update(currentFrame);
        game.Draw(currentFrame);
        currentFrame++;
        game.EndFrame();
    }
    return 0;
}

