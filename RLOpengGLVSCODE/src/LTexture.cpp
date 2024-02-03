#include "LTexture.h"
LTexture::LTexture() {
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture() {
    free();
}

bool LTexture::loadFromFile(SDL_Renderer* renderer, const char *path) {
    free();
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path);
    if(loadedSurface == NULL) {
        printf("Error loading image %s : | IMG_Error: $s\n", path, IMG_GetError());
        return false;
    } else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == NULL) {
            printf("Unable to create texture %s from surface. SDL_Error: %s'n", path, SDL_GetError());
        } else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        mTexture = newTexture;
        SDL_FreeSurface(loadedSurface);
    }
    if(mTexture == NULL) {
        printf("Somehow texture %s still is null, good luck from here lol", path);
        return false;
    }
    return true;
}

void LTexture::render(SDL_Renderer *renderer, int x, int y, SDL_Rect *rect) {
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    if(rect != NULL) {
        renderQuad.w = rect->w;
        renderQuad.h = rect->h;
    }
    SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
}

void LTexture::free() {
    if(mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
