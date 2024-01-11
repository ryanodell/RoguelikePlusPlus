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
    //delete currentScreen;
    currentScreen = &screen;
    currentScreen->OnLoad();
}

void ScreenManager::ChangeScreen(const char* name) {

}

ScreenManager::ScreenManager() {
    // Constructor implementation
}

ScreenManager::~ScreenManager() {
    // Destructor implementation
}
