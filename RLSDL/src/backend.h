#ifndef BACKEND_H
#define BACKEND_H
#include <stdio.h>
#include <assert.h>
#include <unordered_map>
#include <memory>
#include <SDL.h>
#include <SDL_image.h>

struct Vector2D {
public:
    Vector2D(float x, float y);
    float X;
    float Y;    
};

//Vector2D::Vector2D(float x, float y) : X(x), Y(y) { };

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
    SDL_Texture* GetInternalTexture() const { return mInternalTexture; };
    Texture2D(SDL_Texture* texture, int width, int height);
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
    std::unordered_map<const char*, std::shared_ptr<Texture2D>> mTextureCache;
    bool _loadTextureCache(const char* name);
    SDL_Renderer* mRenderer;
};

class Renderer {
public:
    Renderer(SDL_Renderer* renderer);
    void Draw(Texture2D* texture, float x, float y, SDL_Rect rec, SDL_Color color);
    void Draw(Texture2D* texture, Vector2D position, SDL_Rect rec, SDL_Color color);
private:
    SDL_Renderer* mRenderer;
};

#endif