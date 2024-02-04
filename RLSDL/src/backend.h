#ifndef BACKEND_H
#define BACKEND_H
#include <stdio.h>
#include <assert.h>
#include <SDL.h>
#include <SDL_image.h>

class Game {
public:
    Game(int width, int height, const char* windowTitle);
    ~Game();
    bool Init();
    void Run();
    int GetWidth() { return mWidth; };
    int GetHeight() { return mHeight; };
private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    int mWidth;
    int mHeight;
    const char* mWindowTitle;
};

#endif