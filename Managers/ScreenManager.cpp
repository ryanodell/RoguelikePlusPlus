#include "../ScreenManager.h"

#include <iostream>

ScreenManager& ScreenManager::GetInstance() {
    static ScreenManager instance; // The single instance is created only once
    return instance;
}

void ScreenManager::Update(int frame) {
    currentScreen->Update(frame);
}

void ScreenManager::Draw(int frame) {
    currentScreen->Draw(frame);
}

void ScreenManager::ChangeScreen(ScreenBase& screen) {
    currentScreen = &screen;
    currentScreen->OnLoad();
}

ScreenManager::ScreenManager() {
    // Constructor implementation
}

ScreenManager::~ScreenManager() {
    // Destructor implementation
}
