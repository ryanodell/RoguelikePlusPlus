#include "OverworldScreen.h"
#include "../Globals.h"

int PlayerX, PlayerY;

void OverworldScreen::OnLoad() const {
    PlayerX = 3;
    PlayerY = 3;
}

void OverworldScreen::Update(int frame) const {

}

void OverworldScreen::Draw(int frame) const {
    //top border
    for (int i = 0; i < GameWidth + 2; i++) {
        std::cout << '-';
    }
    std::cout << std::endl;

    for (int i = 0; i < GameHeight; i++)
    {
        for (int k = 0; k < GameWidth; k++)
        {
            // Left border
            if (k == 0)
                std::cout << '|';
            // player
            else if (i == PlayerY && k == PlayerX)
                std::cout << '@';
            // Right border
            else if (k + 1 == GameWidth)
                std::cout << '|';
            else
                std::cout << ' ';
        }
        std::cout << std::endl;
    }

        // Draws bottom border
    for (int i = 0; i < GameWidth + 2; i++)
        std::cout << '-';
    std::cout << std::endl;

    //Display current frame:
    std::cout << std::endl;
    std::cout << "Current Frame: " << frame << std::endl;
    std::cout << "X: " << PlayerX << std::endl;
    std::cout << "Y: " << PlayerY << std::endl;
}
