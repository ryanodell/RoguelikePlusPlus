#ifndef SCREENMANAGER_H_INCLUDED
#define SCREENMANAGER_H_INCLUDED


class ScreenManager {

public:
    static ScreenManager& GetInstance();
    static void Update();

private:
    ScreenManager();
    ScreenManager(const ScreenManager&) = delete;
    ScreenManager& operator =(const ScreenManager&) = delete;
    ~ScreenManager();

};


#endif // SCREENMANAGER_H_INCLUDED
