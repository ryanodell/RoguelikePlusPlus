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

bool LTexture::loadFromRenderedText(SDL_Renderer* renderer, TTF_Font* font, const char *text, SDL_Color textColor) {
    free();
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    if(textSurface == NULL) {
        printf("Unable to render text to surface. TTF_Error: %s\n", TTF_GetError());
        return false;
    } else {
        mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(mTexture == NULL) {
            printf("Unable to load surface to texture. SDL_Error: %s\n", SDL_GetError());
            return false;
        } else {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
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

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}
