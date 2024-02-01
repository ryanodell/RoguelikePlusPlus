#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;

SDL_Texture* sTexture = NULL;
SDL_Renderer* sRenderer = NULL;

SDL_Surface* loadSurface(const char* path) {
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path);
	if( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL Error: %s\n", path, SDL_GetError() );
	} else {
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface( loadedSurface, screenSurface->format, 0 );
		if( optimizedSurface == NULL ) {
			printf( "Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}
	return optimizedSurface;
}

void close() {
	SDL_DestroyTexture(sTexture);
	sTexture = NULL;
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
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
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
			screenSurface = SDL_GetWindowSurface(window);
		}
	}
	return true;
}

bool loadMedia() {
	sTexture = loadTexture("../assets/curses_square_16x16.png");
	if(sTexture == NULL) {
		printf("Failed to load texture image\n");
		return false;
	}
	return true;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	printf("Fork");
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
				SDL_RenderClear(sRenderer);

				SDL_Rect topLeftViewport;
				topLeftViewport.x = 0;
				topLeftViewport.y = 0;
				topLeftViewport.w = SCREEN_WIDTH / 2;
				topLeftViewport.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport( sRenderer, &topLeftViewport );
				SDL_RenderCopy(sRenderer, sTexture, NULL, NULL);

				//Top right viewport
				SDL_Rect topRightViewport;
				topRightViewport.x = SCREEN_WIDTH / 2;
				topRightViewport.y = 0;
				topRightViewport.w = SCREEN_WIDTH / 2;
				topRightViewport.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport(sRenderer, &topRightViewport);
				SDL_RenderCopy(sRenderer, sTexture, NULL, NULL);

				SDL_Rect bottomViewport;
				bottomViewport.x = 0;
				bottomViewport.y = SCREEN_HEIGHT / 2;
				bottomViewport.w = SCREEN_WIDTH;
				bottomViewport.h = SCREEN_HEIGHT / 2;
				SDL_RenderSetViewport( sRenderer, &bottomViewport );
				SDL_RenderCopy( sRenderer, sTexture, NULL, NULL );

				SDL_RenderPresent(sRenderer);
			}
		}
	}
    return 0;
}