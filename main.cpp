#include "Game.h"
#include "Globals.h"

bool isRunning = true;
int currentFrame = 1;
int GameWidth = 50;
int GameHeight = 20;

int main() {
    Game game(GameWidth, GameHeight);
    game.OnLoad();
    while(game.IsRunning()) {
        game.Draw(currentFrame);
        game.Update(currentFrame);
        currentFrame++;
        //game.EndFrame();
    }
    return 0;
}

