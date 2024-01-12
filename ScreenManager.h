#ifndef SCREENMANAGER_H_INCLUDED
#define SCREENMANAGER_H_INCLUDED
#include "Screens/ScreenBase.h"
#include "Screens/MainMenuScreen.h"
#include "Screens/OverworldScreen.h"

#include "Globals.h"

class ScreenManager {

public:
    static ScreenManager& GetInstance();
    void OnLoad();
    void Update(int frame);
    void Draw(int frame);
    void ChangeScreen(ScreenBase& screen);
    void ChangeScreen(const char* name);
private:
    ScreenManager();
    ScreenManager(const ScreenManager&) = delete;
    ScreenManager& operator =(const ScreenManager&) = delete;
    ~ScreenManager();
    ScreenBase* currentScreen;
};


#endif // SCREENMANAGER_H_INCLUDED
