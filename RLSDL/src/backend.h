#ifndef BACKEND_H
#define BACKEND_H
#include <stdio.h>
#include <assert.h>
#include <unordered_map>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>

class Game {
public:
    Game(int width, int height, const char* windowTitle);
    ~Game();
    bool Init();
    void Run();
    int GetWidth() const { return mWidth; };
    int GetHeight() const { return mHeight; };
    SDL_Renderer* GetRenderer() const { return mRenderer; }
private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    int mWidth;
    int mHeight;
    const char* mWindowTitle;
};

class Texture2D {
public:
    int GetWidt() const { return mWidth; };
    int GetHeight() const { return mHeight; };
    Texture2D(SDL_Texture* texture);
    ~Texture2D();
private:
    SDL_Texture* mInternalTexture;
    int mWidth;
    int mHeight;
};

class TextureManager {
public:
    void Init(SDL_Renderer* renderer);
    Texture2D* LoadTexture(const char *name);
private:
    // std::unordered_map<const char*, Texture2D*> mTextureCache;
    std::unordered_map<const char*, std::shared_ptr<Texture2D>> mTextureCache;
    //std::unordered_map<const char*, std::shared_ptr<Texture2D>> classMap;
    bool _loadTextureCache(const char* name);
    SDL_Renderer* mRenderer;
};


#endif