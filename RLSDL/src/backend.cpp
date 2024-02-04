#include "backend.h"
#include <assert.h>

Game::Game(int width, int height) : mWidth(width), mHeight(height) {
    if(SDL_Init(SDL_INIT_EVERYTHING) > -1) {
        assert("Err");
    }
}

Game::~Game() {
}

void Game::Init() {

}

void Game::Run() {
}
