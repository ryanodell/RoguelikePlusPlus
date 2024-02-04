#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <windows.h>
#include <iostream>
#include "LTexture.h"
#include <cmath>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Renderer* sRenderer = NULL;

TTF_Font* font = NULL;
LTexture textTexture;


void close() {
	textTexture.free();
	TTF_CloseFont(font);
	SDL_DestroyRenderer(sRenderer);
	SDL_DestroyWindow(window);
	sRenderer = NULL;
	window = NULL;
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

SDL_Texture* loadTexture(const char* path) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path);
    if( loadedSurface == NULL ) {
        printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
    } else {
        newTexture = SDL_CreateTextureFromSurface( sRenderer, loadedSurface );
        if( newTexture == NULL ) {
            printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
        }
        SDL_FreeSurface( loadedSurface );
    }
    return newTexture;
}


bool init() {
	if(SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL Could not be initialized. SDL Error: %s\n", SDL_GetError());
		return false;
	} else {
		if( !SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1" )) {
			printf( "Warning: Linear texture filtering not enabled!" );
		}
		window = SDL_CreateWindow("Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, 
			SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(window == NULL) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			return false;
		} else {
			sRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if(sRenderer == NULL) {
				printf("Could not initialize SDL Renderer | SDL Error: %s\n", SDL_GetError());
				return false;
			}
			SDL_SetRenderDrawColor(sRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			int imgFlags = IMG_INIT_PNG;
			if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
				printf("SDL_Image could not be initialized. SDL_Image Error: %s\n", IMG_GetError());
				return false;
			}
			if(TTF_Init() == -1) {
				printf("SDL_ttf couldn't be initialized! TTF_Error: %s\n", TTF_GetError());
				return false;
			}
		}
	}
	return true;
}

bool loadMedia() {
	font = TTF_OpenFont("../assets/lazy.ttf", 28);
	if(font == NULL) {
		printf("Failed to load font. TTF_Error: %s\n", TTF_GetError());
		return false;
	} else {
		SDL_Color textColor = { 0, 0, 0 };
		if(!textTexture.loadFromRenderedText(sRenderer, font, "The quick brown fox jumps over the lazy dog", textColor ) )
		{
			printf( "Failed to render text texture!\n" );
			return false;
		}
	}
	return true;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	if(!init()) {
		printf("Failed to initialize\n");
		return -1;
	} else {
		if(!loadMedia()) {
			printf("Failed to load media\n");
			return -1;
		} else {
			Uint8 r = 255;
			Uint8 g = 255;
			Uint8 b = 255;

			bool quit = false;
			SDL_Event e;
			while( !quit ) {
				while( SDL_PollEvent( &e ) != 0 ) {
					if( e.type == SDL_QUIT ) {
						quit = true;
					}
				}
				SDL_SetRenderDrawColor(sRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(sRenderer);
				textTexture.render(sRenderer, (SCREEN_WIDTH - textTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - textTexture.getHeight() ) / 2 );

				SDL_RenderPresent(sRenderer);
			}
		}
	}
    return 0;
}