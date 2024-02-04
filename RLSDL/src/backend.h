#ifndef BACKEND_H
#define BACKEND_H
#include <SDL.h>

class Game {
public:
    Game(int width, int height);
    ~Game();
    void Init();
    void Run();
    int GetWidth() { return mWidth; };
    int GetHeight() { return mHeight; };
private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    int mWidth;
    int mHeight;
    
};

#endif