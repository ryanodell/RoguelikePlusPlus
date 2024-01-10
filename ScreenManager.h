#ifndef SCREENMANAGER_H_INCLUDED
#define SCREENMANAGER_H_INCLUDED
#include "Screens/ScreenBase.h"
#include "Screens/MainMenuScreen.h"

class ScreenManager {

public:
    static ScreenManager& GetInstance();
    void OnLoad();
    void Update(int frame);
    void Draw(int frame);
    void ChangeScreen(ScreenBase& screen);

private:
    ScreenManager();
    ScreenManager(const ScreenManager&) = delete;
    ScreenManager& operator =(const ScreenManager&) = delete;
    ~ScreenManager();
    ScreenBase* currentScreen;
    //ScreenBase* currentScreen;
};


#endif // SCREENMANAGER_H_INCLUDED
