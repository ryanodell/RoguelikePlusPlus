#include "backend.h"


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
}
