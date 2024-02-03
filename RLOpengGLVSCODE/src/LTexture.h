#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL_image.h>
#include <stdio.h>

class LTexture
{
public:
    LTexture();
    ~LTexture();
    bool loadFromFile(SDL_Renderer* renderer, const char* path);
    void render(SDL_Renderer* renderer, int x, int y, SDL_Rect* rect = NULL);
    void free();
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    int getWidth() { return mWidth; };
    int getHeight() { return mHeight; };
private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};
#endif