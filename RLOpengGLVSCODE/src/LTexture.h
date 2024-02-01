#ifndef TEXTURE_H
#define TEXTURE_H
#include <SDL_image.h>

class LTexture
{
public:
    LTexture();
    ~LTexture();
    bool loadFromFile(const char* path);
    void render(int x, int y);
    void free();
    int getWidth() { return mWidth; };
    int getHeight() { return mHeight; };
private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};
#endif