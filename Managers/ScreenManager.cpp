#include "../ScreenManager.h"

#include <iostream>

ScreenManager& ScreenManager::GetInstance() {
    static ScreenManager instance; // The single instance is created only once
    return instance;
}

void ScreenManager::Update() {
    std::cout << "Fuck you" << std::endl;
}

ScreenManager::ScreenManager() {
    // Constructor implementation
}

ScreenManager::~ScreenManager() {
    // Destructor implementation
}
