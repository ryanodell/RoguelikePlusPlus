#include "LTexture.h"
LTexture::LTexture(SDL_Renderer* renderer) {
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    mRenderer = renderer;
}

LTexture::~LTexture() {
    free();
}

bool LTexture::loadFromFile(const char *path) {
    free();
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path);
    if(loadedSurface == NULL) {
        printf("Error loading image %s : | IMG_Error: $s\n", path, IMG_GetError());
        return false;
    } else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
        if(newTexture == NULL) {
            printf("Unable to create texture %s from surface. SDL_Error: %s'n", path, SDL_GetError());
        } else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    if(mTexture == NULL) {
        printf("Somehow texture %s still is null, good luck from here lol", path);
        return false;
    }
    mTexture = newTexture;
    return true;
}

void LTexture::render(int x, int y) {
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    SDL_RenderCopy(mRenderer, mTexture, NULL, &renderQuad);
}

void LTexture::free() {
}
