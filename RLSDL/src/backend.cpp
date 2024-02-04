#include "backend.h"

///////////////////////////GAME////////////////////////////////////////
Game::Game(int width, int height, const char* windowTitle) : 
            mWidth(width), 
            mHeight(height), 
            mWindowTitle(windowTitle) {    
}
Game::~Game() {
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    mWindow = NULL;
    mRenderer = NULL;
    IMG_Quit();
    SDL_Quit();
}
bool Game::Init() {
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("There was an error initializing SDL || SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    mWindow = SDL_CreateWindow(mWindowTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        mWidth, mHeight, SDL_WINDOW_SHOWN);
    if(mWindow == NULL) {
        printf("Failed to initialize Window | SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    mRenderer = SDL_CreateRenderer(mWindow, 01, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(mRenderer == NULL) {
        printf("Failed to initialize SDL Renderer | SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
		printf("SDL_Image could not be initialized. SDL_Image Error: %s\n", IMG_GetError());
        return false;
	}
    return true;
}
void Game::Run() {
    TextureManager textureManager;

}
///////////////////////////END GAME////////////////////////////////////////

///////////////////////////TEXTURE2D////////////////////////////////////////
Texture2D::Texture2D(SDL_Texture* texture) {
    mInternalTexture = texture;
}

Texture2D::~Texture2D() {
    if(mInternalTexture != NULL) {
        SDL_DestroyTexture(mInternalTexture);
        mInternalTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}
///////////////////////////END TEXTURE2D////////////////////////////////////////


///////////////////////////TEXTUREMANAGER////////////////////////////////////////
void TextureManager::Init(SDL_Renderer *renderer) {
    //mRenderer = &renderer;
}

Texture2D* TextureManager::LoadTexture(const char* name) {
    auto it = mTextureCache.find(name);
    if(it == mTextureCache.end()) {
        if(_loadTextureCache(name) == false) {            
             printf("Failed to load %s into the texture cache\n", name);            
            return nullptr;
        } 
    }
    return mTextureCache[name].get();
}
bool TextureManager::_loadTextureCache(const char *name) {
    SDL_Texture* newTexture;
    SDL_Surface* loadedSurface = IMG_Load(name);
    if(loadedSurface == NULL) {
        printf("Failed to load surface | IMG_Error: %s\n", IMG_GetError());
        return false;
    } else {
        newTexture = SDL_CreateTextureFromSurface(mRenderer, loadedSurface);
        if(newTexture == NULL) {
            printf("Failed to create texture from surface | SDL_Error: %s\n", SDL_GetError());
            return false;
        } else {
            mTextureCache[name] = std::make_shared<Texture2D>(newTexture);
            SDL_FreeSurface(loadedSurface);
        }
    }
}
///////////////////////////END TEXTUREMANAGER////////////////////////////////////////
