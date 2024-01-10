#include "../ScreenManager.h"

#include <iostream>

ScreenManager& ScreenManager::GetInstance() {
    static ScreenManager instance; // The single instance is created only once
    return instance;
}

void ScreenManager::Update(int frame) {
    std::cout << "Fuck you" << std::endl;
}

void ScreenManager::Draw(int frame) {

}

void ScreenManager::ChangeScreen(MainMenuScreen& screen) {
    tmp = &screen;
    screen.OnLoad();
}

ScreenManager::ScreenManager() {
    // Constructor implementation
}

ScreenManager::~ScreenManager() {
    // Destructor implementation
}
