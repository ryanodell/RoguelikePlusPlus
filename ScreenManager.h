#ifndef SCREENMANAGER_H_INCLUDED
#define SCREENMANAGER_H_INCLUDED
#include "Screens/ScreenBase.h"
#include "Screens/MainMenuScreen.h"

class ScreenManager {

public:
    static ScreenManager& GetInstance();
    static void OnLoad();
    static void Update(int frame);
    static void Draw(int frame);
    void ChangeScreen(MainMenuScreen& screen);

private:
    ScreenManager();
    ScreenManager(const ScreenManager&) = delete;
    ScreenManager& operator =(const ScreenManager&) = delete;
    ~ScreenManager();
    MainMenuScreen* tmp;
    //ScreenBase* currentScreen;
};


#endif // SCREENMANAGER_H_INCLUDED
