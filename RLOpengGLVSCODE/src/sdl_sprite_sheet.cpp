#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <iostream>
#include "LTexture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Renderer* sRenderer = NULL;

LTexture spriteSheet;

SDL_Rect gSpriteClips[4];

void close() {
	spriteSheet.free();
	SDL_DestroyRenderer(sRenderer);
	SDL_DestroyWindow(window);
	sRenderer = NULL;
	window = NULL;
	IMG_Quit();
	SDL_Quit();
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
		}
	}
	return true;
}

bool loadMedia() {
	if(!spriteSheet.loadFromFile(sRenderer, "../assets/dots.png")) {
		printf("Failed to load spriteSheet texture");
		return false;
	}
	gSpriteClips[ 0 ].x =   0;
	gSpriteClips[ 0 ].y =   0;
	gSpriteClips[ 0 ].w = 100;
	gSpriteClips[ 0 ].h = 100;
	//Set top right sprite
	gSpriteClips[ 1 ].x = 100;
	gSpriteClips[ 1 ].y =   0;
	gSpriteClips[ 1 ].w = 100;
	gSpriteClips[ 1 ].h = 100;
	
	//Set bottom left sprite
	gSpriteClips[ 2 ].x =   0;
	gSpriteClips[ 2 ].y = 100;
	gSpriteClips[ 2 ].w = 100;
	gSpriteClips[ 2 ].h = 100;
	//Set bottom right sprite
	gSpriteClips[ 3 ].x = 100;
	gSpriteClips[ 3 ].y = 100;
	gSpriteClips[ 3 ].w = 100;
	gSpriteClips[ 3 ].h = 100;
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
				spriteSheet.render(sRenderer, 0, 0, &gSpriteClips[ 0 ] );
				spriteSheet.render(sRenderer, SCREEN_WIDTH - gSpriteClips[ 1 ].w, 0, &gSpriteClips[ 1 ] );
				spriteSheet.render(sRenderer, 0, SCREEN_HEIGHT - gSpriteClips[ 2 ].h, &gSpriteClips[ 2 ] );
				spriteSheet.render(sRenderer, SCREEN_WIDTH - gSpriteClips[ 3 ].w, SCREEN_HEIGHT - gSpriteClips[ 3 ].h, &gSpriteClips[ 3 ] );
				SDL_RenderPresent(sRenderer);
			}
		}
		close();
	}
    return 0;
}