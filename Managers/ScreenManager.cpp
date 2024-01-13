#include "../ScreenManager.h"
#include <iostream>

MainMenuScreen mainMenuScreen;
OverworldScreen overworldScreen;


ScreenManager& ScreenManager::GetInstance() {
    static ScreenManager instance; // The single instance is created only once
    return instance;
}

void ScreenManager::Update(int frame) {
    currentScreen->Update(frame);
}

void ScreenManager::Draw(int frame) {
    RenderManager::ClearScreen();
    currentScreen->Draw(frame);
    RenderManager::Render();
}

void ScreenManager::ChangeScreen(ScreenBase& screen) {
    //delete currentScreen;
    currentScreen = &screen;
    currentScreen->OnLoad();
}

void ScreenManager::ChangeScreen(const char* name) {
    if(strcmp(name, "mainMenu") == 0) {
        //std::cout << "main" << std::endl;
        currentScreen = &mainMenuScreen;
    }
    if(strcmp(name, "overworld") == 0) {
        //std::cout << "overworld" << std::endl;
        currentScreen = &overworldScreen;
    }
    currentScreen->OnLoad();
}

ScreenManager::ScreenManager() {
    // Constructor implementation
}

ScreenManager::~ScreenManager() {
    // Destructor implementation
}
